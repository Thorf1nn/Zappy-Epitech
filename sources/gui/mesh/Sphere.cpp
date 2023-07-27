#include "Sphere.hpp"

namespace zappy {
    Sphere::Sphere(float radius, int rings, int slices, Vector3 position)
        : _radius(radius), _rings(rings), _slices(slices), _position(position) {}

    Mesh Sphere::create() {
        return GenMeshSphere(_radius, _rings, _slices);
    }

    void Sphere::draw(Color color) {
        DrawSphere(_position, _radius, color);
    }
}
