#include "Window.hpp"

namespace zappy {
    Window::Window(uint16_t screenWidth, uint16_t screenHeight, const std::string title) : _screenWidth(screenWidth), _screenHeight(screenHeight), _title(title) {}

    void Window::init() {
        InitWindow(WIN_WIDTH, WIN_HEIGHT, _title.c_str());
        // InitAudioDevice();
        _camera3D.position = {1.0f, 50.0f, 0.0f};
        _camera3D.target = {0.0f, 0.0f, 0.0f};
        _camera3D.up = {0.0f, 1.0f, 0.0f};
        _camera3D.fovy = 50.0f;
        _camera3D.projection = CAMERA_PERSPECTIVE;
    }

    void Window::updateCamera() {
        UpdateCamera(&_camera3D, CAMERA_THIRD_PERSON);
    }

    void Window::setFPS(int fps) {
        SetTargetFPS(fps);
    }

    bool Window::isOpen() {
        return !WindowShouldClose();
    }

    void Window::clearBackground(Color color) {
        ClearBackground(color);
    }

    void Window::beginDrawing() {
        BeginDrawing();
    }

    void Window::endDrawing() {
        EndDrawing();
    }

    void Window::beginMode3D() {
        BeginMode3D(_camera3D);
    }

    void Window::endMode3D() {
        EndMode3D();
    }

    void Window::drawFPS(int posX, int posY) {
        DrawFPS(posX, posY);
    }

    Camera3D Window::getCamera() {
        return (this->_camera3D);
    }

    Window::~Window() {
        std::cout << "Window destructor" << std::endl;
        CloseWindow();
    }
} // zappy