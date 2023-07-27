#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_IMESH_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_IMESH_HPP

#include "raylib.h"

namespace zappy {
    class IMesh {
    public:
        IMesh() = default;
        virtual ~IMesh() = default;

        virtual Mesh create() = 0;
        virtual void draw(Color color) = 0;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_IMESH_HPP
