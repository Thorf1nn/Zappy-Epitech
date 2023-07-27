#include "Texture.hpp"

namespace zappy {
    void Texture::load(const std::string& path) {
        _texture = LoadTexture(path.c_str());
    }

    void Texture::update(Color color) {
        UpdateTexture(_texture, &color);
    }

    void Texture::draw(Vector2 position, Color color) {
        DrawTextureV(_texture, position, color);
    }

    Texture::~Texture() {
        // UnloadTexture(_texture);
    }

    Texture2D Texture::get() const {
        return _texture;
    }
} // zappy