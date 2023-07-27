#include "Egg.hpp"

namespace zappy {
    Egg::Egg(int id) : _id(id) {}

    void Egg::setPosition(const uint16_t x, const uint16_t y) {
        _position.first = x;
        _position.second = y;
    }

    std::pair<uint16_t, uint16_t> Egg::getPosition() const {
        return _position;
    }

    int Egg::getId() const {
        return _id;
    }

} // zappy