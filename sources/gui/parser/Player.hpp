#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_PLAYER_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

namespace zappy {
    enum Orientation {
        NORTH = 1,
        EAST = 2,
        SOUTH = 3,
        WEST = 4
    };

    class Player {
    public:
        Player(int id);
        ~Player() = default;

        int getId() const;
        std::pair<float, float> getPosition() const;
        std::pair<float, float> getTarget() const;
        int getLevel() const;
        Orientation getOrientation() const;
        float getSpeed() const;
        std::string getMessage() const;
        float getRadius() const;
        std::string getTeamName() const;

        std::unordered_map<std::string, uint16_t> getInventory() const;

        void setTeamName(std::string teamName);
        void setPosition(float x, float y);
        void setTarget(float x, float y);
        void setLevel(uint16_t level);
        void setResource(std::string& resourceKey, uint16_t quantity);
        void setOrientation(int orientation);
        void setRadius(float radius);
        void setMessage(std::string newMessage);
        void incRadius(float increment);

        void addQuantity(uint16_t resourceNumber, uint16_t quantity);
        void removeQuantity(uint16_t resourceNumber, uint16_t quantity);

        void setBroadcastMessage(const std::string& message);
        std::string getMessageBroadcast() const;

        bool getExpulsion() const;
        void setExpulsion(bool expulsion);

        bool initialised;

    private:
        std::string _teamName;
        float _speed;
        int _id;
        std::pair<float, float> _position;
        std::pair<float, float> _target;
        uint16_t _level;
        Orientation _orientation;
        float _broadcastRadius;
        std::string _broadcastMessage;
        bool _expulsion;
        std::unordered_map<std::string, uint16_t> _inventory;
    };
} // zappy
#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_PLAYER_HPP
