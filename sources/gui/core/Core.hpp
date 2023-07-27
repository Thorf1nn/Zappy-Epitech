/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Core
*/

#ifndef B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CORE_HPP
#define B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CORE_HPP

#include <iostream>
#include "Server.hpp"

#include "Menu.hpp"
#include "Game.hpp"
#include "Music.hpp"

#define LOCALHOST "127.0.0.1"

namespace zappy {
    class Core {
    public:
        Core(int port, std::string& machine);
        ~Core() = default;

        void run();

    private:
        int _port;
        std::string _machine;
        Infos _infos;
    };
} // zappy

#endif //B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_CORE_HPP