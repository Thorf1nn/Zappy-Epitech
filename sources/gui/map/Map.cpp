/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Map
*/

#include "Map.hpp"

namespace zappy {
    Map::Map() : _cube(1.0f, 1.0f, 1.0f), _created(false), _timer(false),
                _backgroundCube{Cube(15.0f, 1000.0f, 500.0f, {-200.0f, 0.0f, 0.0f}), Cube(15.0f, 1000.0f, 500.0f, {200.0f, 0.0f, 0.0f}), Cube(500.0f, 1000.0f, 15.0f, {0.0f, 0.0f, -200.0f}), Cube(500.0f, 1000.0f, 15.0f, {0.0f, 0.0f, 200.0f})} {
        _food       = LoadModel("sources/gui/assets/resources/oxygen.glb");
        _linemate   = LoadModel("sources/gui/assets/resources/1linemate.glb");
        _deraumere  = LoadModel("sources/gui/assets/resources/2deraumere.glb");
        _sibur      = LoadModel("sources/gui/assets/resources/3sibur.glb");
        _mendiane   = LoadModel("sources/gui/assets/resources/4mendiane.glb");
        _phiras     = LoadModel("sources/gui/assets/resources/5phiras.glb");
        _thystame   = LoadModel("sources/gui/assets/resources/6thystame.glb");

        // _food       .transform = MatrixRotateX(-1.5708);
        _linemate   .transform = MatrixRotateX(-1.5708);
        _deraumere  .transform = MatrixRotateX(-1.5708);
        _sibur      .transform = MatrixRotateX(-1.5708);
        _mendiane   .transform = MatrixRotateX(-1.5708);
        _phiras     .transform = MatrixRotateX(-1.5708);
        _thystame   .transform = MatrixRotateX(-1.5708);
    }

    void Map::init(Server& server) {
        server.receive();
        Infos infos = server.getParser().getInfos();

        Vector3 bgPositions[4] = { {-200.0f, 0.0f, 0.0}, {200.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -200.0f}, {0.0f, 0.0f, 200.0f} };
        _cubeModel.loadFromMesh(_cube.create());
        _mapTexture[0].load("sources/gui/assets/stone.png");
        _backgroundTexture.load("sources/gui/assets/skys.png");
        _cubeModel.get().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _mapTexture[0].get();
        for (int i = 0; i < 4; i++) {
            _backgroundModel[i].loadFromMesh(_backgroundCube[i].create());
            _backgroundModel[i].setPosition(bgPositions[i]);
            _backgroundModel[i].get().materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _backgroundTexture.get();
        }
        _platformSize = 7;
        _spaceBetweenPlatforms = 3;
        _redPlanet.setPath("sources/gui/assets/planet.glb");
        _redPlanet.setPosition(Vector3 {40.0f, 50.0f, 80.0f});
        _redPlanet.load();
        _greyPlanet.setPath("sources/gui/assets/planet2.glb");
        _greyPlanet.setPosition(Vector3 {0, 45.0f, -50.0f});
        _greyPlanet.load();
        _clickedIslandX = 0;
        _clickedIslandZ = 0;
        _isClicked = false;
        _isClickedPlayer = false;

        _texture.load("sources/gui/assets/UI/cordonates.png");


        _foodTexture.load("sources/gui/assets/food.png");
        _linemateTexture.load("sources/gui/assets/linemate.png");
        _deraumereTexture.load("sources/gui/assets/deraumere.png");
        _siburTexture.load("sources/gui/assets/sibur.png");
        _mendianeTexture.load("sources/gui/assets/mendiane.png");
        _phirasTexture.load("sources/gui/assets/phiras.png");
        _thystameTexture.load("sources/gui/assets/thystame.png");

        // _logoResources.load("sources/gui/assets/food.png");
        // _logoResources[1].load("sources/gui/assets/linemate.png");
        // _logoResources[2].load("sources/gui/assets/deraumere.png");
        // _logoResources[3].load("sources/gui/assets/sibur.png");
        // _logoResources[4].load("sources/gui/assets/mendiane.png");
        // _logoResources[5].load("sources/gui/assets/phiras.png");
        // _logoResources[6].load("sources/gui/assets/thystame.png");
        createIslands(infos);
    }

    void Map::setCamera(Camera3D camera) {
        _camera = camera;
    }

    void Map::setCameraBehave() {
        const float rotationSpeed = 0.000001f;

        if (IsKeyDown(KEY_LEFT))
            _camera.target.x -= rotationSpeed;
        if (IsKeyDown(KEY_RIGHT))
            _camera.target.x += rotationSpeed;
        if (IsKeyDown(KEY_UP))
            _camera.target.y -= rotationSpeed;
        if (IsKeyDown(KEY_DOWN))
            _camera.target.y += rotationSpeed;
    }

    void Map::update(Server& server) {
        _timer += GetFrameTime();
        if (_timer >= 0.3f) {
            updateResources(server);
            // _inventory.allInventory(server, _islands);
            _timer = 0;
        }
        handleClick();
        setCameraBehave();
    }

    void Map::initClickedPlayer(std::shared_ptr<Player> clickedPlayer) {
        _clickedPlayer = clickedPlayer;
    }

    void Map::handleClick() {
        Vector2 mousePosition = GetMousePosition();
        Ray mouseRay = GetMouseRay(mousePosition, _camera);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            bool clickedOnPlatform = false;
            for (const auto& island : _islands) {
                const auto& islandPos = island->getPos();
                const auto islandSize = island->getSize();
                _clickedIslandX = islandPos.x / 10;
                _clickedIslandZ = islandPos.z / 10;
                Vector3 minPoint = { islandPos.x - islandSize, islandPos.y - islandSize, islandPos.z - islandSize };
                Vector3 maxPoint = { islandPos.x + islandSize, islandPos.y + islandSize,  islandPos.z + islandSize };
                BoundingBox islandBoundingBox = { minPoint, maxPoint };

                if (GetRayCollisionBox(mouseRay, islandBoundingBox).hit) {
                    if (_clickedIsland != nullptr && _clickedIsland != island) {
                        _clickedIsland->resetPosition(_allPositions);
                    }
                    _clickedIsland = island;
                    clickedOnPlatform = true;
                    break;
                }
            }
            if (!clickedOnPlatform && _clickedIsland != nullptr) {
                _clickedIsland->resetPosition(_allPositions);
                _clickedIsland = nullptr;
            } else if (_clickedIsland != nullptr) {
                if (_clickedIsland->_pos.y > 0) {
                    _clickedIsland->resetPosition(_allPositions);
                    _isClicked = false;
                } else {
                    _clickedIsland->onClick();
                    _isClicked = true;
                }
            }
        }
    }

    // TODO: faire une fonction à part pour créer les ressources (si on a le temps)
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

    void Map::updateResources(Server& server) {
        for (auto& island : _islands) {
            int gui_linemate = 0;
            int gui_deraumere = 0;
            int gui_sibur = 0;
            int gui_mendiane = 0;
            int gui_phiras = 0;
            int gui_thystame = 0;
            int gui_food = 0;

            int posX = (island.get()->getPos().x + _decayX) / 10;
            int posY = (island.get()->getPos().z + _decayZ) / 10;
            std::string request("bct " + std::to_string(posX) + " " + std::to_string(posY) + "\n");
            server.send(request);
            server.receive();

            std::unordered_map<std::string, int> updatedResources = server.getParser().getInfos().getTileMap(posX, posY).value().get().getResources();
            std::vector<std::unique_ptr<Resource>>& resources = island.get()->getResources();

            for (auto& currentResource : resources) {
                if (currentResource.get()->getName() == "food") {
                    gui_food++;
                }
                if (currentResource.get()->getName() == "linemate") {
                    gui_linemate++;
                }
                if (currentResource.get()->getName() == "deraumere") {
                    gui_deraumere++;
                }
                if (currentResource.get()->getName() == "sibur") {
                    gui_sibur++;
                }
                if (currentResource.get()->getName() == "mendiane") {
                    gui_mendiane++;
                }
                if (currentResource.get()->getName() == "phiras") {
                    gui_phiras++;
                }
                if (currentResource.get()->getName() == "thystame") {
                    gui_thystame++;
                }
            }

            for (auto &newResource : updatedResources) {
                if (newResource.first == "food") {
                    while (gui_food < newResource.second) {
                        std::unique_ptr<Resource> resource = std::make_unique<Resource>("food", island.get()->getPos());
                        resources.push_back(std::move(resource));
                        gui_food++;
                    }
                    while (gui_food > newResource.second) {
                        auto result = std::find_if(resources.begin(), resources.end(), [](const std::unique_ptr<Resource>& resource) {
                            return resource.get()->getName() == "food";
                        });
                        resources.erase(result);
                        gui_food--;
                    }
                }
                if (newResource.first == "linemate") {
                    while (gui_linemate < newResource.second) {
                        std::unique_ptr<Resource> resource = std::make_unique<Resource>("linemate", island.get()->getPos());
                        resources.push_back(std::move(resource));
                        gui_linemate++;
                    }
                    while (gui_linemate > newResource.second) {
                        auto result = std::find_if(resources.begin(), resources.end(), [](const std::unique_ptr<Resource>& resource) {
                            return resource.get()->getName() == "linemate";
                        });
                        resources.erase(result);
                        gui_linemate--;
                    }
                }
                if (newResource.first == "deraumere") {
                    while (gui_deraumere < newResource.second) {
                        std::unique_ptr<Resource> resource = std::make_unique<Resource>("deraumere", island.get()->getPos());
                        resources.push_back(std::move(resource));
                        gui_deraumere++;
                    }
                    while (gui_deraumere > newResource.second) {
                        auto result = std::find_if(resources.begin(), resources.end(), [](const std::unique_ptr<Resource>& resource) {
                            return resource.get()->getName() == "deraumere";
                        });
                        resources.erase(result);
                        gui_deraumere--;
                    }
                }
                if (newResource.first == "sibur") {
                    while (gui_sibur < newResource.second) {
                        std::unique_ptr<Resource> resource = std::make_unique<Resource>("sibur", island.get()->getPos());
                        resources.push_back(std::move(resource));
                        gui_sibur++;
                    }
                    while (gui_sibur > newResource.second) {
                        auto result = std::find_if(resources.begin(), resources.end(), [](const std::unique_ptr<Resource>& resource) {
                            return resource.get()->getName() == "sibur";
                        });
                        resources.erase(result);
                        gui_sibur--;
                    }
                }
                if (newResource.first == "mendiane") {
                    while (gui_mendiane < newResource.second) {
                        std::unique_ptr<Resource> resource = std::make_unique<Resource>("mendiane", island.get()->getPos());
                        resources.push_back(std::move(resource));
                        gui_mendiane++;
                    }
                    while (gui_mendiane > newResource.second) {
                        auto result = std::find_if(resources.begin(), resources.end(), [](const std::unique_ptr<Resource>& resource) {
                            return resource.get()->getName() == "mendiane";
                        });
                        resources.erase(result);
                        gui_mendiane--;
                    }
                }
                if (newResource.first == "phiras") {
                    while (gui_phiras < newResource.second) {
                        std::unique_ptr<Resource> resource = std::make_unique<Resource>("phiras", island.get()->getPos());
                        resources.push_back(std::move(resource));
                        gui_phiras++;
                    }
                    while (gui_phiras > newResource.second) {
                        auto result = std::find_if(resources.begin(), resources.end(), [](const std::unique_ptr<Resource>& resource) {
                            return resource.get()->getName() == "phiras";
                        });
                        resources.erase(result);
                        gui_phiras--;
                    }
                }
                if (newResource.first == "thystame") {
                    while (gui_thystame < newResource.second) {
                        std::unique_ptr<Resource> resource = std::make_unique<Resource>("thystame", island.get()->getPos());
                        resources.push_back(std::move(resource));
                        gui_thystame++;
                    }
                    while (gui_thystame > newResource.second) {
                        auto result = std::find_if(resources.begin(), resources.end(), [](const std::unique_ptr<Resource>& resource) {
                            return resource.get()->getName() == "thystame";
                        });
                        resources.erase(result);
                        gui_thystame--;
                    }
                }
            }
        }
    }

    void Map::getState(bool isClickedPlayer) {
        _isClickedPlayer = isClickedPlayer;
    }

    void Map::draw2D(Server& server) {
        if (_isClicked) {
            _inventory.slideIn();
        } else {
            _inventory.slideOut();
            _inventory.playersSlideOut();
        }
        if (_clickedIsland) {
            _inventory.printInventory(_clickedIsland);
        }

        if (_isClickedPlayer) {
            _inventory.playersSlideIn();
        } else {
            _inventory.playersSlideOut();
        }
        if (_clickedPlayer) {
            _inventory.playerInventory(_clickedPlayer, server);
        }
        _inventory.allInventory(server, _islands);

        _foodTexture.draw({     1853, 848}, WHITE);
        _linemateTexture.draw({ 1853, 888}, WHITE);
        _deraumereTexture.draw({1853, 918}, WHITE);
        _siburTexture.draw({    1853, 948}, WHITE);
        _mendianeTexture.draw({ 1853, 980}, WHITE);
        _phirasTexture.draw({   1853, 1012}, WHITE);
        _thystameTexture.draw({ 1853, 1039}, WHITE);

        std::string cordonatesX = std::to_string(_clickedIslandX);
        std::string cordonatesY = std::to_string(_clickedIslandZ);
        _texture.draw({532, -22}, WHITE);
        _text.drawText("Island coordinates | X:", WIN_WIDTH / 2 - 250, 30, 30, WHITE);
        _text.drawText(" Z:", WIN_WIDTH / 2 + 150, 30, 30, WHITE);
        _text.drawText(std::to_string(std::atoi(cordonatesX.c_str())).c_str(), WIN_WIDTH / 2 + 100, 30, 30, WHITE);
        _text.drawText(std::to_string(std::atoi(cordonatesY.c_str())).c_str(), WIN_WIDTH / 2 + 200, 30, 30, WHITE);
    }

    void Map::draw() {
        for (auto &island : _islands) {
            island.get()->_cubeModel.draw(island.get()->getPos(), island.get()->getSize(), WHITE);
            for (auto &resource : island.get()->getResources())
            {
                Vector3 resPos = resource.get()->getPosition();
                if (resource.get()->getName() == "food") {
                    resPos.y += 2;
                    DrawModel(_food, resPos, .03f, WHITE);
                } else if (resource.get()->getName() == "linemate") {
                    DrawModel(_linemate, resPos, 1.0f, WHITE);
                } else if (resource.get()->getName() == "deraumere") {
                    DrawModel(_deraumere, resPos, 1.0f, WHITE);
                } else if (resource.get()->getName() == "sibur") {
                    DrawModel(_sibur, resPos, 1.0f, WHITE);
                } else if (resource.get()->getName() == "phiras") {
                    DrawModel(_phiras, resPos, 1.0f, WHITE);
                } else if (resource.get()->getName() == "mendiane") {
                    DrawModel(_mendiane, resPos, 1.0f, WHITE);
                } else if (resource.get()->getName() == "thystame") {
                    DrawModel(_thystame, resPos, 1.0f, WHITE);
                }
            }
        }

        for (int  i = 0; i < 4; i++) {
            _backgroundModel[i].draw(_backgroundModel[i].getPosition(), 1.0f, WHITE);
        }

        _redPlanet.draw(_redPlanet.getPosition(), 10.0f, WHITE);
        _greyPlanet.draw(_greyPlanet.getPosition(), 10.0f, WHITE);
    }

    Map::~Map() {

    }
}
