/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Game
*/

#include "Game.hpp"

namespace zappy {
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
}
