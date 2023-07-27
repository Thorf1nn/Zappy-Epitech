#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_WINDOW_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_WINDOW_HPP

#include "raylib.h"
#include "Camera.hpp"
#include <iostream>
#include "../map/Map.hpp"

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080

namespace zappy {
    class Window {
    public:
        Window(uint16_t screenWidth, uint16_t screenHeight, const std::string title);
        ~Window();

        void init();

        void setFPS(int fps);
        bool isOpen();
        void clearBackground(Color color);
        void updateCamera();
        void beginDrawing();
        void endDrawing();
        void beginMode3D();
        void endMode3D();
        void drawFPS(int posX, int posY);
        Camera3D getCamera();

    private:
        Camera _camera;
        Camera3D _camera3D;
        uint16_t _screenWidth;
        uint16_t _screenHeight;
        std::string _title;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_WINDOW_HPP
