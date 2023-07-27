/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Inventory
*/

#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <map>
#include "raylib.h"
#include <stdbool.h>

#include "Platform.hpp"
#include "Player.hpp"
#include "Texture.hpp"
#include "Text.hpp"
#include "Server.hpp"

namespace zappy {
    class Inventory {
    public:
        Inventory();
        ~Inventory();
        void printInventory(std::shared_ptr<Platform> clickedIsland);
        void playerInventory(std::shared_ptr<Player> clickedPlayer, Server& server);

        void resetPos(void);
        bool slideIn(void);
        bool slideOut(void);
        bool playersSlideIn(void);
        bool playersSlideOut(void);
        void allInventory(Server& server, std::vector<std::shared_ptr<Platform>> islands);

    private:
        Texture _playersTexture;
        Texture _islandsTexture;
        Texture _inventoryTexture;
        Texture _allInventoryTexture;

        Vector2 _tilesPosition;
        Vector2 _playersPosition;
        Vector2 _inventoryPosition;


        Text _text;
        float _speed;
    };
}

#endif /* !INVENTORY_HPP_ */
