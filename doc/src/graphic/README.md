---
sidebar: auto
---

# Graphical

# Le Dossier CORE
## le core

Au sein de ce dossier il existe plusieurs fichiers ayant pour chacune des fonctions propres à eux;
le fichier `core` lui, est l'équivalent de la machine de contrôle du projet c'est ici que vous pouvez retrouver tout
les appels de fonctions.

```cpp
    void Core::run() {
        Server server(_port, _machine);
        server.create();
        server.connect();
        server.send("GRAPHIC\n");

        Window window(1920, 1080, "Zappy");
        window.init();

        InitAudioDevice();
        MusicGame music("sources/gui/assets/audio/mini1111.xm");
        music.load();
        music.loop(true);
        music.play();
        // music.setVolume(50.0f);

        GameState gameState = MENU;
        Menu menu(gameState);
        Game game(gameState);
        game.init(server);

        while (window.isOpen()) {
            UpdateMusicStream(music.get());
            switch (gameState) {
                case MENU:
                    gameState = menu.handleEvents();
                    menu.update();
                    break;
                case GAME:
                    gameState = game.handleEvents();
                    game.update(server);
                    break;
            }

            window.updateCamera();
            window.beginDrawing();
            window.clearBackground(BLACK);

             switch (gameState) {
                 case MENU:
                    menu.draw();
                    break;
                case QUIT:
                    exit(0);
                    break;
                case SETTINGS:
                    std::cout << "SETTINGS\n";
                    break;
                case GAME:
                    window.beginMode3D();
                     Camera3D cam = window.getCamera();
                     game.setCamera(cam);
                    game.draw(server);
                    window.endMode3D();
                    game.draw2D(server);
                    break;
             }
             window.endDrawing();
         }
        server.close();
    } // zappy
```


## Le game

C'est au sein de cette fonction que bon nombres d'init son fait et que beaucoup de d'affichage sont effectués

```cpp

    Game::Game(GameState& gameState) : _gameState(gameState) {}

    void Game::init(Server& server) {
        _map.init(server);
        _bot.setPath("sources/gui/assets/little_astronaut.glb");
        _bot.setPosition(Vector3 {10, 3, 10});
        _bot.load();
        _egg.setPath("sources/gui/assets/egg.glb");
        _egg.load();
    }

    Game::~Game() {
        std::cout << "destroy game" << std::endl;
    }

    GameState Game::handleEvents() {
        return GAME;
    }

    void Game::update(Server& server) {
        _map.update(server);
    }

    void Game::setCamera(Camera3D camera) {
        _camera3D = camera;
        _map.setCamera(_camera3D);
    }

    void Game::draw2D(Server& server) {
        _map.draw2D(server);
    }

    void Game::draw(Server& server) {
        float dt = GetFrameTime();
        server.receive();
        Infos infos = server.getParser().getInfos();
        _map.draw();

        std::vector<Egg> eggs = infos.getEggs();
        for (auto& egg : eggs) {
            Vector3 eggPosition {egg.getPosition().first * 10 - _decayX, 3, egg.getPosition().second * 10 - _decayZ};
            _egg.draw(eggPosition, 0.01f, WHITE);
        }

        std::vector<std::shared_ptr<Player>> players_ptr = infos.getPlayers();
        _lenZ = infos.getSizeMap().first;
        _lenX = infos.getSizeMap().second;
        _decayX = (_lenX * (7 + 3) / 2 - 7);
        _decayZ = (_lenZ * (7 + 3) / 2 - 7);

        Vector2 mousePosition = GetMousePosition();
        Ray mouseRay = GetMouseRay(mousePosition, _camera3D);

        for (auto &player : infos.getPlayers()) {
            auto [posX, posY] = player.get()->getPosition();
            auto [targetX, targetY] = player.get()->getTarget();
            if (posX < targetX) {
                posX += player.get()->getSpeed() * dt;
            }
            if (posX > targetX) {
                posX -= player.get()->getSpeed() * dt;
            }
            if (posY < targetY) {
                posY += player.get()->getSpeed() * dt;
            }
            if (posY > targetY) {
                posY -= player.get()->getSpeed() * dt;
            }

            player.get()->setPosition(posX, posY);
            Vector3 playerPosition { posX * 10 - _decayX, 3.5f, posY * 10 - _decayZ };
            _bot.draw(playerPosition, 4.0f, WHITE);

            Vector3 playerMinPoint = { playerPosition.x - 10, playerPosition.y - 10, playerPosition.z - 10 };
            Vector3 playerMaxPoint = { playerPosition.x + 10, playerPosition.y + 10, playerPosition.z + 10 };
            BoundingBox playerBoundingBox = { playerMinPoint, playerMaxPoint };

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (GetRayCollisionBox(mouseRay, playerBoundingBox).hit) {
                    if (_clickedPlayer != nullptr) {
                        _clickedPlayer = player;
                        _map.initClickedPlayer(_clickedPlayer);
                        _isClicked = !_isClicked;
                        _map.getState(_isClicked);
                        std::cout << "Clicked: " << _isClicked << std::endl;
                    } else {
                        _clickedPlayer = player;
                        _map.initClickedPlayer(_clickedPlayer);
                        _isClicked = true;
                        _map.getState(_isClicked);
                        std::cout << "Clicked: " << _isClicked << std::endl;
                    }
                }
            }
        }
    }
```

# Le Dossier Map

## Le fichier map

Ce fichier est lui responsable de la création de la map, il va créer les îles, les ressources et tout l'environnement présent
lorsque le graphique est lancé.

```cpp

    void Map::createIslands(Infos &infos) {
        std::srand(std::time(nullptr));
        float platformX = 0.0f, platformZ = 0.0f;
        _lenZ = infos.getSizeMap().first;
        _lenX = infos.getSizeMap().second;
        _decayX = (_lenX * (_platformSize + _spaceBetweenPlatforms) / 2 - _platformSize);
        _decayZ = (_lenZ * (_platformSize + _spaceBetweenPlatforms) / 2 - _platformSize);
        int id = 0;

        for (auto& tileMap : infos.getTilesMap()) {
            auto rscs = tileMap.getResources();
            auto [line, column] = tileMap.getPosition();
            platformX = column * (_platformSize + _spaceBetweenPlatforms);
            platformZ = line * (_platformSize + _spaceBetweenPlatforms);
            _platformPosition = Vector3{platformX - _decayX, 0, platformZ - _decayZ};
            std::shared_ptr<Platform> platform = std::make_shared<Platform>(_platformPosition, _platformSize);
            for (auto& [key, value] : rscs) {
                for (int i = 0; i < value; i++) {
                    std::unique_ptr<Resource> resource = std::make_unique<Resource>(key, _platformPosition);
                    platform.get()->getResources().push_back(std::move(resource));
                }
            }
            _allPositions.push_back(_platformPosition);
            platform->setIndex(id);
            _islands.push_back(std::move(platform));
            id++;
        }
    }
```

## Le fichier Platforms

Ce fichier est responsable du stockage du contenu des platforms et de son actualisation.

```cpp

    Platform::Platform() : _cube(1.0f, 1.0f, 1.0f), _isElevated(true) {}

    Platform::Platform(Vector3 pos, float size) : _cube(1.0f, 1.0f, 1.0f) {
        _pos = pos;
        _size = size;
        _cubeModel.loadFromMesh(_cube.create());
        _texture.load("sources/gui/assets/stone.png");
        _cubeModel.get().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture.get();
    }

    Vector3 Platform::getPos() {
        return _pos;
    }

    void Platform::setIndex(int index) {
        _islandIndex = index;
    }

    void Platform::getIndex() {
        std ::cout << _islandIndex << std::endl;
    }

    bool Platform::isElevated() {
        std::cout << "posy" << _pos.y << std::endl;
        if (_pos.y > 0)
            return true;
        return false;
    }

    std::vector<std::unique_ptr<Resource>>& Platform::getResources() {
        return _resources;
    }

    std::unordered_map<std::string, int> Platform::getResourcesQuantity() {
        for (auto& resource : _resources) {
            _resourcesQuantity[resource->getName()]++;
        }
        return _resourcesQuantity;
    }

    BoundingBox Platform::getHitbox() {
        return _hitbox;
    }

    float Platform::getSize() {
        return _size;
    }

    void Platform::onClick() {
        _pos.y += 0.8;
    }

    void Platform::resetPosition(std::vector<Vector3>& allPositions) {
        if (_islandIndex < allPositions.size()) {
            _pos.y = allPositions[_islandIndex].y;
        }
    }

    Platform::~Platform()
    {
    }
}
```

# Le Dossier Parser
# Le fichier Parser

Ce fichier est lui responsable de toute la récupération des données par rapport au serveur, il va regrouper toutes les fonctions qui vont permettre d'être utilisé afin de les afficher sur le `GUI`. Vous pouvez également voir la présence d'une `factory` qui favorise l'abstraction.

```cpp
    Parser::Parser() {
        _commands = {
                {"msz", [this](std::string& secondString) -> void { return getSizeMap(secondString); }},
                {"mct", [this](std::string& secondString) -> void { return getAllTilesMap(secondString); }},
                {"bct", [this](std::string& secondString) -> void { return getContentOfTile(secondString); }},
                {"tna", [this](std::string& secondString) -> void { return getTeamName(secondString); }},
                {"pnw", [this](std::string& secondString) -> void { return newPlayerConnection(secondString); }},
                {"ppo", [this](std::string& secondString) -> void { return getPlayerPosition(secondString); }},
                {"plv", [this](std::string& secondString) -> void { return getPlayerLevel(secondString); }},
                {"pin", [this](std::string& secondString) -> void { return getPlayerInventory(secondString); }},
                {"pex", [this](std::string& secondString) -> void { return expulsion(secondString); }},
                {"pbc", [this](std::string& secondString) -> void { return broadcast(secondString); }},
                {"pic", [this](std::string& secondString) -> void { return startIncantation(secondString); }},
                {"pie", [this](std::string& secondString) -> void { return endIncantation(secondString); }},
                {"pfk", [this](std::string& secondString) -> void { return eggLaying(secondString); }},
                {"pdr", [this](std::string& secondString) -> void { return getResourceDropping(secondString); }},
                {"pgt", [this](std::string& secondString) -> void { return getResourceCollecting(secondString); }},
                {"pdi", [this](std::string& secondString) -> void { return getDeathOfPlayer(secondString); }},
                {"enw", [this](std::string& secondString) -> void { return eggCreation(secondString); }},
                {"ebo", [this](std::string& secondString) -> void { return playerConnectionForEgg(secondString); }},
                {"edi", [this](std::string& secondString) -> void { return getDeathOfEgg(secondString); }},
                {"sgt", [this](std::string& secondString) -> void { return timeUnitRequest(secondString); }},
                {"sst", [this](std::string& secondString) -> void { return timeUnitModification(secondString); }},
                {"seg", [this](std::string& secondString) -> void { return endOfGame(secondString); }},
                {"smg", [this](std::string& secondString) -> void { return messageFromServer(secondString); }},
                {"suc", [this](std::string& secondString) -> void { return unknownCommand(secondString); }},
                {"sbp", [this](std::string& secondString) -> void { return badParameter(secondString); }},
        };

        _resourceKeys = {
                "food",
                "linemate",
                "deraumere",
                "sibur",
                "mendiane",
                "phiras",
                "thystame"
        };
    }
```