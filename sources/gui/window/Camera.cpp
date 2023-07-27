#include "Camera.hpp"

namespace zappy {
    Camera::Camera(const Vector3& position, const Vector3& target, const Vector3& up, float fov) {
        _camera.position = position;
        _camera.target = target;
        _camera.up = up;
        _camera.fovy = fov;
    }

    Camera3D Camera::getCamera() const {
        return _camera;
    }

    Camera::~Camera() {
        std::cout << "Camera destroyed" << std::endl;
    }
} // zappy