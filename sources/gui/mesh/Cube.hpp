#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CUBE_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CUBE_HPP

#include "AMesh.hpp"

namespace zappy {
    class Cube : public AMesh {
    public:
        Cube(float width, float height, float length, Vector3 position = {0, 0, 0});
        ~Cube() override = default;

        Mesh create() override;
        void draw(Color color) override;

    private:
        float _width;
        float _height;
        float _length;
        Vector3 _position;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CUBE_HPP
