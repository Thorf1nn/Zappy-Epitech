#include "Infos.hpp"
#include <algorithm>

namespace zappy {
    void Infos::setSizeMap(uint16_t x, uint16_t y) {
        _sizeMap.first = x;
        _sizeMap.second = y;
        std::cout << "Size map: " << _sizeMap.first << " " << _sizeMap.second << std::endl;
    }

    std::pair<uint16_t, uint16_t> Infos::getSizeMap() const {
        return _sizeMap;
    }

    void Infos::setTeamName(std::string teamName) {
        _teamsName.push_back(teamName);
    }

    std::vector<std::string> Infos::getTeamsName() const {
        return _teamsName;
    }

    std::string Infos::getTeamName(std::string teamName) {
        auto result = std::find_if(_teamsName.begin(), _teamsName.end(), [&teamName](std::string& name) {
            return name == teamName;
        });
        if (result != _teamsName.end()) {
            return *result;
        }
        throw std::runtime_error("Team name not found");
    }

    void Infos::addTileMap(TileMap tileMap) {
        _tilesMap.push_back(tileMap);
    }

    std::vector<TileMap> Infos::getTilesMap() const {
        return _tilesMap;
    }

    std::optional<std::reference_wrapper<TileMap>> Infos::getTileMap(uint16_t x, uint16_t y) {
        auto iter = std::find_if(_tilesMap.begin(), _tilesMap.end(), [&x, &y](const TileMap& tileMap) {
            return tileMap.getPosition().first == x && tileMap.getPosition().second == y;
        });

        if (iter != _tilesMap.end()) {
            return std::ref(*iter);
        } else {
            return std::nullopt;
        }
    }

    void Infos::addPlayer(Player player) {
        _players.push_back(std::make_shared<Player>(player));
    }

    std::vector<std::shared_ptr<Player>> Infos::getPlayers() {
        return _players;
    }

    void Infos::removePlayer(int id) {
        auto result = std::find_if(_players.begin(), _players.end(), [&id](const std::shared_ptr<Player>& player) {
            return player->getId() == id;
        });

        if (result != _players.end()) {
            _players.erase(result);
        }
    }

    std::shared_ptr<Player> Infos::getPlayer(int id) {
        auto result = std::find_if(_players.begin(), _players.end(), [&id](const std::shared_ptr<Player>& player) {
            return player.get()->getId() == id;
        });
        if (result != _players.end()) {
            return *result;
        }
        throw std::runtime_error("Player not found");
    }

    void Infos::removeEgg(int id) {
        auto result = std::find_if(_eggs.begin(), _eggs.end(), [&id](Egg& egg) {
            return egg.getId() == id;
        });
        if (result != _eggs.end()) {
            _eggs.erase(result);
        }
    }

    void Infos::addEgg(Egg egg) {
        _eggs.push_back(egg);
    }

    Egg& Infos::getEgg(int id) {
        auto result = std::find_if(_eggs.begin(), _eggs.end(), [&id](Egg& egg) {
            return egg.getId() == id;
        });
        if (result != _eggs.end()) {
            return *result;
        }
        throw std::runtime_error("Egg not found");
    }

    std::vector<Egg> Infos::getEggs() const {
        return _eggs;
    }

    void Infos::print() const {
        std::cout << "size map: " << _sizeMap.first << " " << _sizeMap.second << std::endl;
        std::cout << "teams name: ";
        for (auto& teamName : _teamsName) {
            std::cout << teamName << " ";
        }
        std::cout << std::endl;
        std::cout << "tiles map: " << std::endl;
        for (auto& tileMap : _tilesMap) {
            std::cout << "pos: " << tileMap.getPosition().first << " " << tileMap.getPosition().second << std::endl;
            for (auto& resource : tileMap.getResources()) {
                std::cout << resource.first << ": " << resource.second << std::endl;
            }
        }
        std::cout << "----------------------------" << std::endl;
    }
}
