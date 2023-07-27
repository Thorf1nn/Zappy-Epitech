#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_INFOS_H
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_INFOS_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <memory>
#include <optional>

#include "TileMap.hpp"
#include "Player.hpp"
#include "Egg.hpp"

namespace zappy {
    class Infos {
    public:
        Infos() = default;
        ~Infos() = default;

        void setSizeMap(uint16_t x, uint16_t y);
        std::pair<uint16_t, uint16_t> getSizeMap() const;

        void setTeamName(std::string teamName);
        std::vector<std::string> getTeamsName() const;
        std::string getTeamName(std::string teamName);

        void addTileMap(TileMap tileMap);
        std::vector<TileMap> getTilesMap() const;
        std::optional<std::reference_wrapper<TileMap>> getTileMap(uint16_t x, uint16_t y);

        void addPlayer(Player player);
        std::vector<std::shared_ptr<Player>> getPlayers();
        std::shared_ptr<Player> getPlayer(int id);
        void removePlayer(int id);

        Egg& getEgg(int id);
        void addEgg(Egg egg);
        void removeEgg(int id);
        std::vector<Egg> getEggs() const;

        void print() const;

    private:
        std::pair<uint16_t, uint16_t> _sizeMap;
        std::vector<std::string> _teamsName;

        std::vector<TileMap> _tilesMap;
        std::vector<std::shared_ptr<Player>> _players;
        std::vector<Egg> _eggs;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_INFOS_H
