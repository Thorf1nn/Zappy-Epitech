#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_Sprite_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_Sprite_HPP

#include "raylib.h"
#include <iostream>

namespace zappy {
    class Sprite {
    public:
        Sprite();
        explicit Sprite(std::string& path);
        ~Sprite();

        void setPath(std::string);
        void setPosition(Vector3);

        void load();
        void loadFromMesh(Mesh mesh);
        void draw(Vector3 position, float scale, Color color);

        Model get() const;
        Vector3 getPosition();

    private:
        std::string _path;
        Vector3 _position;
        Model _model;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_Sprite_HPP
