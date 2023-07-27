#include "Sprite.hpp"

namespace zappy {
    Sprite::Sprite() {}

    Sprite::Sprite(std::string& path) : _path(path) {
    }

    void Sprite::load() {
        _model = LoadModel(_path.c_str());
    }

    void Sprite::setPath(std::string newPath) {
        _path = newPath;
    }

    void Sprite::setPosition(Vector3 newPos) {
        _position = newPos;
    }

    void Sprite::loadFromMesh(Mesh mesh) {
        _model = LoadModelFromMesh(mesh);
    }

    void Sprite::draw(Vector3 position, float scale, Color color) {
        DrawModel(_model, position, scale, color);
    }

    Model Sprite::get() const {
        return _model;
    }

    Vector3 Sprite::getPosition() {
        return _position;
    }

    Sprite::~Sprite() {
        // UnloadModel(_model);
    }
} // zappy