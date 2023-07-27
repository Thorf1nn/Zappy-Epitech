#include "Player.hpp"

namespace zappy {
    Player::Player(int id) : _id(id), _level(0), _expulsion(false)
    {
        _speed = 4;
    }

    void Player::setTeamName(std::string teamName) {
        _teamName = teamName;
    }

    std::string Player::getTeamName() const {
        return _teamName;
    }

    void Player::setPosition(float x, float y) {
        _position.first = x;
        _position.second = y;
    }

    void Player::setTarget(float x, float y) {
        _target.first = x;
        _target.second = y;
    }

    void Player::setLevel(uint16_t level) {
        _level = level;
    }

    void Player::setOrientation(int orientation) {
        _orientation = static_cast<Orientation>(orientation);
    }

    std::unordered_map<std::string, uint16_t> Player::getInventory() const {
        return _inventory;
    }

    void Player::setBroadcastMessage(const std::string& message) {
        _broadcastMessage = message;
    }

    std::string Player::getMessageBroadcast() const {
        return _broadcastMessage;
    }

    float Player::getSpeed() const {
        return _speed;
    }


    bool Player::getExpulsion() const {
        return _expulsion;
    }

    void Player::setExpulsion(bool expulsion) {
        _expulsion = expulsion;
    }

    void Player::setResource(std::string& resourceKey, uint16_t quantity) {
        _inventory[resourceKey] = quantity;
    }

    void Player::setMessage(std::string newMessage) {
        _broadcastMessage = newMessage;
    }

    void Player::setRadius(float radius) {
        _broadcastRadius = radius;
    }

    void Player::incRadius(float increment) {
        _broadcastRadius += increment;
    }

    void Player::addQuantity(uint16_t resourceNumber, uint16_t quantity) {
        switch (resourceNumber) {
            case 0:
                _inventory["food"] += quantity;
                break;
            case 1:
                _inventory["linemate"] += quantity;
                break;
            case 2:
                _inventory["deraumere"] += quantity;
                break;
            case 3:
                _inventory["sibur"] += quantity;
                break;
            case 4:
                _inventory["mendiane"] += quantity;
                break;
            case 5:
                _inventory["phiras"] += quantity;
                break;
            case 6:
                _inventory["thystame"] += quantity;
                break;
        }
    }

    void Player::removeQuantity(uint16_t resourceNumber, uint16_t quantity) {
        switch (resourceNumber) {
            case 0:
                _inventory["food"] -= quantity;
                break;
            case 1:
                _inventory["linemate"] -= quantity;
                break;
            case 2:
                _inventory["deraumere"] -= quantity;
                break;
            case 3:
                _inventory["sibur"] -= quantity;
                break;
            case 4:
                _inventory["mendiane"] -= quantity;
                break;
            case 5:
                _inventory["phiras"] -= quantity;
                break;
            case 6:
                _inventory["thystame"] -= quantity;
                break;
        }
    }

    int Player::getId() const {
        return _id;
    }

    std::pair<float, float> Player::getPosition() const {
        return _position;
    }

    std::pair<float, float> Player::getTarget() const {
        return _target;
    }

    std::string Player::getMessage() const {
        return _broadcastMessage;
    }

    float Player::getRadius() const {
        return _broadcastRadius;
    }

    int Player::getLevel() const {
        return _level;
    }

    Orientation Player::getOrientation() const {
        return _orientation;
    }
} // zappy