#ifndef AMESH_HPP_
#define AMESH_HPP_

#include "IMesh.hpp"

namespace zappy {
    class AMesh : public IMesh {
    public:
        ~AMesh() override = default;

        virtual void drawMesh(Mesh mesh, Material material, Matrix transform);
    private:
    };
}

#endif /* !AMESH_HPP_ */
