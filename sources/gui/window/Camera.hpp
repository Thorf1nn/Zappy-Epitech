#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CAMERA_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CAMERA_HPP

#include "raylib.h"
#include <iostream>

namespace zappy {
    class Camera {
    public:
        Camera() = default;
        Camera(const Vector3& position, const Vector3& target, const Vector3& up, const float fovy);
        ~Camera();

        Camera3D getCamera() const;

    private:
        Camera3D _camera;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CAMERA_HPP
