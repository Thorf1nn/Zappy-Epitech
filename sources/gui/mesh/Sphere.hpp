#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "AMesh.hpp"

namespace zappy {
    class Sphere : public AMesh {
    public:
        Sphere() = default;
        Sphere(float radius, int rings, int slices, Vector3 position = {0, 0, 0});
        ~Sphere() override = default;

        Mesh create() override;
        void draw(Color color) override;

    private:
        float _radius;
        int _rings;
        int _slices;
        Vector3 _position;
    };
}

#endif /* !SPHERE_HPP_ */
