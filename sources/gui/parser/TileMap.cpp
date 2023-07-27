#include "TileMap.hpp"

namespace zappy {
    void TileMap::setPosition(uint16_t x, uint16_t y) {
        _position.first = x;
        _position.second = y;
    }

    void TileMap::setResource(std::string& resourceKey, int quantity) {
        _resources[resourceKey] = quantity;
    }

    std::pair<uint16_t, uint16_t> TileMap::getPosition() const {
        return _position;
    }

    std::unordered_map<std::string, int> TileMap::getResources() const {
        return _resources;
    }

    int TileMap::getResource(std::string& resourceKey) {
        return _resources[resourceKey];
    }

    void TileMap::setIncantation(int result) {
        // Anti warning temporary protection
        if (result)
        {
            return;
        }
    }

    void TileMap::addQuantity(uint16_t resourceNumber, uint16_t quantity) {
        switch (resourceNumber) {
            case 0:
                _resources["food"] += quantity;
                break;
            case 1:
                _resources["linemate"] += quantity;
                break;
            case 2:
                _resources["deraumere"] += quantity;
                break;
            case 3:
                _resources["sibur"] += quantity;
                break;
            case 4:
                _resources["mendiane"] += quantity;
                break;
            case 5:
                _resources["phiras"] += quantity;
                break;
            case 6:
                _resources["thystame"] += quantity;
                break;
        }
    }

    void TileMap::removeQuantity(uint16_t resourceNumber, uint16_t quantity) {
        switch (resourceNumber) {
            case 0:
                _resources["food"] -= quantity;
                break;
            case 1:
                _resources["linemate"] -= quantity;
                break;
            case 2:
                _resources["deraumere"] -= quantity;
                break;
            case 3:
                _resources["sibur"] -= quantity;
                break;
            case 4:
                _resources["mendiane"] -= quantity;
                break;
            case 5:
                _resources["phiras"] -= quantity;
                break;
            case 6:
                _resources["thystame"] -= quantity;
                break;
        }
    }
} // zappy