/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "raylib.h"
#include "GameState.hpp"
#include "Map.hpp"
#include <memory>
#include <string>

namespace zappy {
    class Game {
    public:
        Game(GameState& gameState);
        ~Game();

        void init(Server& server);

        const Map& getMap() const;
        void setCamera(Camera3D camera);

        GameState handleEvents();
        void update(Server& server);
        void draw(Server& server);
        void draw2D(Server& server);

    private:
        int _lenZ;
        int _lenX;
        int _decayZ;
        int _decayX;
        bool _isClicked;

        std::shared_ptr<Player> _clickedPlayer;

        Map _map;
        Sprite _bot;
        Sprite _egg;
        Inventory _inventory;
        GameState _gameState;
        Camera3D _camera3D;
        Infos _infos;
    };
}

#endif /* !GAME_HPP_ */
