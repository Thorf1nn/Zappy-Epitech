#include "AMesh.hpp"

namespace zappy {
    void AMesh::drawMesh(Mesh mesh, Material material, Matrix transform) {
        DrawMesh(mesh, material, transform);
    }
} // zappy