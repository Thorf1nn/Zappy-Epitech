/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Inventory
*/

#include "Inventory.hpp"

namespace zappy {
    Inventory::Inventory() {
        _tilesPosition.x = -250;
        _playersPosition.y = -250;
        _playersPosition.x = -250;
        _speed = 500;
        _playersTexture.load("sources/gui/assets/UI/PLAYER.png");
        _islandsTexture.load("sources/gui/assets/UI/ISLAND.png");
        _inventoryTexture.load("sources/gui/assets/UI/INVENTORY.png");
        _allInventoryTexture.load("sources/gui/assets/UI/allInventory.png");

    }

    void Inventory::resetPos(void) {
        _tilesPosition.y = 0;
    }

    bool Inventory::slideIn() {
        float dt = GetFrameTime();
        if (_tilesPosition.x < 0) {
            _tilesPosition.x += _speed * dt;
            return false;
        }
        return true;
    }

    bool Inventory::slideOut() {
        float dt = GetFrameTime();
        if (_tilesPosition.x > -250) {
            _tilesPosition.x -= _speed * dt;
            return false;
        }
        return true;
    }

    bool Inventory::playersSlideIn() {
        float dt = GetFrameTime();
        if (_playersPosition.x < 0) {
            _playersPosition.x += _speed * dt;
            return false;
        }
        return true;
    }

    bool Inventory::playersSlideOut() {
        float dt = GetFrameTime();
        if (_playersPosition.x > -250) {
            _playersPosition.x -= _speed * dt;
            return false;
        }
        return true;
    }

    void Inventory::allInventory(Server& server, std::vector<std::shared_ptr<Platform>> islands) {
        // server.send("mct\n");
        // server.receive();
        // std::vector<TileMap> tilesMap = server.getParser().getInfos().getTilesMap();
        int food        = 0;
        int linemate    = 0;
        int deraumere   = 0;
        int sibur       = 0;
        int mendiane    = 0;
        int phiras      = 0;
        int thystame    = 0;

        for (auto &island : islands)
        {
            for (auto &res : island.get()->getResources())
            {
                if (res.get()->getName() == "food") {
                    food++;
                }
                if (res.get()->getName() == "linemate") {
                    linemate++;
                }
                if (res.get()->getName() == "deraumere") {
                    deraumere++;
                }
                if (res.get()->getName() == "sibur") {
                    sibur++;
                }
                if (res.get()->getName() == "mendiane") {
                    mendiane++;
                }
                if (res.get()->getName() == "phiras") {
                    phiras++;
                }
                if (res.get()->getName() == "thystame") {
                    thystame++;
                }
            }
        }

        _allInventoryTexture.draw({1650, 795}, WHITE);
        _text.drawText("food:",        1700, 870,  20, BLACK);
        _text.drawText("linemate:",    1700, 900,  20, BLACK);
        _text.drawText("deraumere",    1700, 930,  20, BLACK);
        _text.drawText("sibur:",       1700, 960,  20, BLACK);
        _text.drawText("mendiane:",    1700, 990,  20, BLACK);
        _text.drawText("phiras:",      1700, 1020, 20, BLACK);
        _text.drawText("thystame:",    1700, 1050, 20, BLACK);

        _text.drawText(std::to_string(food).c_str(),        1830, 870,  20, BLACK);
        _text.drawText(std::to_string(linemate).c_str(),    1830, 900,  20, BLACK);
        _text.drawText(std::to_string(deraumere).c_str(),   1830, 930,  20, BLACK);
        _text.drawText(std::to_string(sibur).c_str(),       1830, 960,  20, BLACK);
        _text.drawText(std::to_string(mendiane).c_str(),    1830, 990,  20, BLACK);
        _text.drawText(std::to_string(phiras).c_str(),      1830, 1020, 20, BLACK);
        _text.drawText(std::to_string(thystame).c_str(),    1830, 1050, 20, BLACK);
    }

    void Inventory::playerInventory(std::shared_ptr<Player> clickedPlayer, Server& server) {
        int idPlayer = clickedPlayer.get()->getId();
        server.send("pin " + std::to_string(idPlayer) + "\n");
        server.receive();

        std::unordered_map<std::string, uint16_t> updateInventory = server.getParser().getInfos().getPlayer(idPlayer).get()->getInventory();
        server.send("plv " + std::to_string(idPlayer) + "\n");
        server.receive();
        int playerLevel = server.getParser().getInfos().getPlayer(idPlayer).get()->getLevel();

        int posY = 640;

       _playersTexture.draw({_playersPosition.x, 580}, WHITE);
        for (const auto& update : updateInventory) {
            std::string text = "Name: " + update.first + " x" + std::to_string(update.second);
            _text.drawText(text.c_str(), _playersPosition.x, posY, 20, BLACK);
            posY += 30;
        }

        _text.drawText(std::string("Player " + std::to_string(idPlayer)).c_str(), _playersPosition.x + 3, 870, 20, BLACK);
        _text.drawText(std::string("Level " +  std::to_string(playerLevel)).c_str() , _playersPosition.x + 3, 890, 20, BLACK);
    }

    void Inventory::printInventory(std::shared_ptr<Platform> clickedIsland) {
        std::cout << "print inventory tile map\n";
        int baseOffset = 0;
        int incrementOffset = 20;
        std::map<std::string, int> resourceCount;
        _islandsTexture.draw({_tilesPosition.x, 70}, WHITE);

        for (auto& resource : clickedIsland->getResources()) {
            std::string source = resource->getName();
            resourceCount[source]++;
        }
        _text.drawText("Inventory ", _tilesPosition.x + 10, 140, 20, BLACK);
        if (clickedIsland->getResources().empty())
            _text.drawText("No resources", _tilesPosition.x + 10, 160, 20, BLACK);
        for (const auto& pair : resourceCount) {
            std::string source = pair.first;
            int count = pair.second;
            std::string displayText = "| resource: " + source;
            if (count > 1)
                displayText += " x" + std::to_string(count);
            _text.drawText(displayText.c_str(), _tilesPosition.x + 10, 160 + baseOffset, 20, BLACK);
            baseOffset += incrementOffset;
        }
    }
    Inventory::~Inventory() {}
}
