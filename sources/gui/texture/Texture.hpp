#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_TEXTURE_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_TEXTURE_HPP

#include "raylib.h"
#include <iostream>

namespace zappy {
    class Texture {
    public:
        Texture() = default;
        explicit Texture(const std::string path);
        ~Texture();

        Texture(const Texture& texture) = default;

        void load(const std::string& path);
        void loadFromImage(Image image);
        void update(Color color);
        void draw(Vector2 position, Color color);
        Texture2D get() const;

    private:
        std::string _path;
        Texture2D _texture;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_TEXTURE_HPP
