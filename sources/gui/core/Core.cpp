/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Core
*/

#include "Core.hpp"

namespace zappy {
    Core::Core(int port, std::string& machine) : _port(port), _machine(machine) {}

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
    }
} // zappy