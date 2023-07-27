/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Menu
*/

#include "Menu.hpp"

namespace zappy {
    Menu::Menu(GameState& gameState) : _gameState(gameState), _playButtonPressed(false), _settingsButtonPressed(false), _exitButtonPressed(false) {
        _playButton = { 90, 300, 536, 714 };
        _settingsButton = { 710, 300, 536, 714 };
        _exitButton = { 1320, 300, 536, 714 };
        _backgroundTexture.load("sources/gui/assets/UI/background.png");
        _playTexture.load("sources/gui/assets/UI/playB.png");
        _settingsTexture.load("sources/gui/assets/UI/settingsB.png");
        _exitTexture.load("sources/gui/assets/UI/quitB.png");
    }

    Menu::~Menu() {}

    GameState Menu::handleEvents() {
        if (CheckCollisionPointRec(GetMousePosition(), _playButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            return GAME;
        }
        if (CheckCollisionPointRec(GetMousePosition(), _exitButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            return QUIT;
        }
        return MENU;
    }

    void Menu::update() {}

    void Menu::draw() {
        _backgroundTexture.draw({0, 0}, WHITE);
        _playTexture.draw({_playButton.x, _playButton.y}, WHITE);
        _settingsTexture.draw({_settingsButton.x, _settingsButton.y}, WHITE);
        _exitTexture.draw({_exitButton.x, _exitButton.y}, WHITE);

        // DrawRectangleRec(playButton, _playButtonPressed ? DARKGRAY : LIGHTGRAY);
        // DrawText("PLAY", playButton.x + 50, playButton.y + 15, 20, _playButtonPressed ? LIGHTGRAY : DARKGRAY);
    }
}
