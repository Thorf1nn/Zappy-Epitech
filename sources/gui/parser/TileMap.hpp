#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_TILEMAP_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_TILEMAP_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

namespace zappy {
    class TileMap {
    public:
        void setPosition(uint16_t x, uint16_t y);
        void setResource(std::string& resourceKey, int quantity);

        std::pair<uint16_t, uint16_t> getPosition() const;
        std::unordered_map<std::string, int> getResources() const;
        int getResource(std::string& resourceKey);
        void setIncantation(int result);

        void addQuantity(uint16_t resourceNumber, uint16_t quantity);
        void removeQuantity(uint16_t resourceNumber, uint16_t quantity);

    private:
        std::pair<uint16_t, uint16_t> _position;
        std::unordered_map<std::string, int> _resources;
        bool _startIncantation;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_TILEMAP_HPP
