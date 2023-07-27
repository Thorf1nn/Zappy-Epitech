/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include <sstream>

#include "Utils.hpp"
#include "Infos.hpp"

namespace zappy {
    class Parser {
    public:
        Parser();
        ~Parser();

        void getCommands(std::string& line);

        void getSizeMap(std::string& secondString);
        void getAllTilesMap(std::string& secondString);
        void getContentOfTile(std::string& secondString);
        void getTeamName(std::string& secondString);
        void newPlayerConnection(std::string& secondString);
        void getPlayerPosition(std::string& secondString);
        void getPlayerLevel(std::string& secondString);
        void getPlayerInventory(std::string& secondString);
        void expulsion(std::string& secondString);
        void broadcast(std::string& secondString);
        void startIncantation(std::string& secondString);
        void endIncantation(std::string& secondString);
        void eggLaying(std::string& secondString);
        void getResourceDropping(std::string& secondString);
        void getResourceCollecting(std::string& secondString);
        void getDeathOfPlayer(std::string& secondString);
        void eggCreation(std::string& secondString);
        void playerConnectionForEgg(std::string& secondString);
        void getDeathOfEgg(std::string& secondString);
        void timeUnitRequest(std::string& secondString);
        void timeUnitModification(std::string& secondString);
        void endOfGame(std::string& secondString);
        void messageFromServer(std::string& secondString);
        void unknownCommand(std::string& secondString);
        void badParameter(std::string& secondString);

        Infos& getInfos();

        int _testX = 0;
        int _testY = 0;

    private:
        std::unordered_map<std::string, std::function<void(std::string& secondString)>> _commands;

        Infos _infos;
        std::vector<std::string> _resourceKeys;
        int i = 0;
    };
}

#endif /* !PARSER_HPP_ */
