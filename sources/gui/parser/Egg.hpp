#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_EGG_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_EGG_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

namespace zappy {
    class Egg {
    public:
        Egg(int id);
        void setPosition(const uint16_t x, const uint16_t y);
        std::pair<uint16_t, uint16_t> getPosition() const;
        int getId() const;

    private:
        int _id;
        std::pair<uint16_t, uint16_t> _position;
    };
} // zappy
#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_EGG_HPP
