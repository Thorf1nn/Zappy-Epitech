/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "raylib.h"
#include "GameState.hpp"
#include "Texture.hpp"

namespace zappy {
    class Menu {
    public:
        Menu(GameState& gameState);
        ~Menu();

        GameState handleEvents();
        void update();
        void draw();

    private:
        GameState _gameState;
        Texture _backgroundTexture;

        Rectangle _playButton;
        bool _playButtonPressed;
        Texture _playTexture;

        Rectangle _settingsButton;
        bool _settingsButtonPressed;
        Texture _settingsTexture;

        Rectangle _exitButton;
        bool _exitButtonPressed;
        Texture _exitTexture;
    };
}


#endif /* !MENU_HPP_ */
