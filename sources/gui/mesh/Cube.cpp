#include "Cube.hpp"

namespace zappy {
    Cube::Cube(float width, float height, float length, Vector3 position)
        : _width(width), _height(height), _length(length), _position(position) {}

    Mesh Cube::create() {
        return GenMeshCube(_width, _height, _length);
    }

    void Cube::draw(Color color) {
        DrawCube(_position, _width, _height, _length, color);
    }
} // zappy
