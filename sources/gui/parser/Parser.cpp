#include "Parser.hpp"

namespace zappy {
    Parser::Parser() {
        _commands = {
                {"msz", [this](std::string& secondString) -> void { return getSizeMap(secondString); }},
                {"mct", [this](std::string& secondString) -> void { return getAllTilesMap(secondString); }},
                {"bct", [this](std::string& secondString) -> void { return getContentOfTile(secondString); }},
                {"tna", [this](std::string& secondString) -> void { return getTeamName(secondString); }},
                {"pnw", [this](std::string& secondString) -> void { return newPlayerConnection(secondString); }},
                {"ppo", [this](std::string& secondString) -> void { return getPlayerPosition(secondString); }},
                {"plv", [this](std::string& secondString) -> void { return getPlayerLevel(secondString); }},
                {"pin", [this](std::string& secondString) -> void { return getPlayerInventory(secondString); }},
                {"pex", [this](std::string& secondString) -> void { return expulsion(secondString); }},
                {"pbc", [this](std::string& secondString) -> void { return broadcast(secondString); }},
                {"pic", [this](std::string& secondString) -> void { return startIncantation(secondString); }},
                {"pie", [this](std::string& secondString) -> void { return endIncantation(secondString); }},
                {"pfk", [this](std::string& secondString) -> void { return eggLaying(secondString); }},
                {"pdr", [this](std::string& secondString) -> void { return getResourceDropping(secondString); }},
                {"pgt", [this](std::string& secondString) -> void { return getResourceCollecting(secondString); }},
                {"pdi", [this](std::string& secondString) -> void { return getDeathOfPlayer(secondString); }},
                {"enw", [this](std::string& secondString) -> void { return eggCreation(secondString); }},
                {"ebo", [this](std::string& secondString) -> void { return playerConnectionForEgg(secondString); }},
                {"edi", [this](std::string& secondString) -> void { return getDeathOfEgg(secondString); }},
                {"sgt", [this](std::string& secondString) -> void { return timeUnitRequest(secondString); }},
                {"sst", [this](std::string& secondString) -> void { return timeUnitModification(secondString); }},
                {"seg", [this](std::string& secondString) -> void { return endOfGame(secondString); }},
                {"smg", [this](std::string& secondString) -> void { return messageFromServer(secondString); }},
                {"suc", [this](std::string& secondString) -> void { return unknownCommand(secondString); }},
                {"sbp", [this](std::string& secondString) -> void { return badParameter(secondString); }},
        };

        _resourceKeys = {
                "food",
                "linemate",
                "deraumere",
                "sibur",
                "mendiane",
                "phiras",
                "thystame"
        };
    }

    Parser::~Parser() {
    }


    void Parser::getCommands(std::string& line) {
        std::string command;

        std::for_each(_commands.begin(), _commands.end(), [&](auto& mapCommand) {
            if (line.find(mapCommand.first) != std::string::npos) {
                command = mapCommand.first;
            }
        });

        std::string commandSecondPart = Utils::split(line, ' ', 1).second;
        if (_commands.find(command) != _commands.end()) {
            return _commands.find(command)->second(commandSecondPart);
        }
    }

    Infos& Parser::getInfos() {
        return _infos;
    }

    void Parser::getSizeMap(std::string& secondString) {
        auto [posX, posY] = Utils::split(secondString, ' ', 1);
        _infos.setSizeMap(std::stoi(posX), std::stoi(posY));
    }

    void Parser::getAllTilesMap(std::string& secondString) {
        std::cout << "command mct" << std::endl;
        std::cout << "params = " << secondString << std::endl;
        // thibault le suceur de bites
    }

    void Parser::getContentOfTile(std::string& secondString) {
        // X Y q0 q1 q2 q3 q4 q5 q6\n
        auto [posX, posY] = Utils::split(secondString, ' ', 0, 4);

        auto tileMap = _infos.getTileMap(std::stoi(posX), std::stoi(posY));
        if (tileMap != std::nullopt) {
            TileMap& updatedTileMap = tileMap.value();
            for (size_t i = 0; i < _resourceKeys.size(); ++i) {
                int quantity = std::stoi(Utils::getNumberAtIndex(secondString, ' ', i + 2));
                updatedTileMap.setResource(_resourceKeys[i], quantity);
            }
        } else {
            TileMap tileMap;
            tileMap.setPosition(std::stoi(posX), std::stoi(posY));

            for (size_t i = 0; i < _resourceKeys.size(); ++i) {
                int quantity = std::stoi(Utils::getNumberAtIndex(secondString, ' ', i + 2));
                tileMap.setResource(_resourceKeys[i], quantity);
            }
            _infos.addTileMap(tileMap);
        }
    }

    void Parser::getTeamName(std::string& secondString) {
        std::string teamName = Utils::split(secondString, ' ', 1).first;
        _infos.setTeamName(teamName);
    }

    void Parser::newPlayerConnection(std::string& secondString) {
        // pnw #n X Y O L N\n
        int id = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 0));
        float posX = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));
        float posY = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 2));
        int orientation = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 3));
        int level = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 4));
        std::string teamName = Utils::getNumberAtIndex(secondString, ' ', 5);

        Player player(id);
        player.setPosition(posX, posY);
        player.setOrientation(orientation);
        player.setLevel(level);
        player.setTeamName(teamName);
        _infos.addPlayer(player);
    }

    void Parser::getPlayerPosition(std::string& secondString) {
        int id = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 0));
        float posX = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));
        float posY = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 2));
        int orientation = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 3));

        std::shared_ptr<Player> player = _infos.getPlayer(id);
        if (!player.get()->initialised) {
            player.get()->setPosition(posX, posY);
            player.get()->initialised = true;
        }
        player.get()->setTarget(posX, posY);
        player.get()->setOrientation(orientation);
    }

    void Parser::getPlayerLevel(std::string& secondString) {
        int id = std::stoi(Utils::split(secondString, ' ', 1).first);
        int level = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));

        std::shared_ptr<Player> player = _infos.getPlayer(id);
        player.get()->setLevel(level);
    }

    void Parser::getPlayerInventory(std::string& secondString) {
        int id = std::stoi(Utils::split(secondString, ' ', 1).first);
        uint16_t posX = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));
        uint16_t posY = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 2));

        std::shared_ptr<Player> player = _infos.getPlayer(id);
        for (size_t i = 0; i < _resourceKeys.size(); i++) {
            int quantity = std::stoi(Utils::split(secondString, ' ', 3 + (i * 2), 4 + (i * 2)).first);
            player.get()->setResource(_resourceKeys[i], quantity);
        }
    }

    void Parser::expulsion(std::string& secondString) {
        // pex n\n
        int id = std::stoi(Utils::split(secondString, ' ', 1).first);

        std::shared_ptr<Player> player = _infos.getPlayer(id);
        player.get()->setExpulsion(true);
    }

    void Parser::broadcast(std::string& secondString) {
        // pbc n M\n
        int id = std::stoi(Utils::split(secondString, ' ', 1).first);
        std::string message = Utils::split(secondString, ' ', 2).first;

        std::shared_ptr<Player> player = _infos.getPlayer(id);
        player.get()->setBroadcastMessage(message);
    }

    void Parser::startIncantation(std::string& secondString) {
        // ANTI WARNING PROTECTION
        if (secondString == "")
        {
            return;
        }
        // uint16_t posX = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 0));
        // uint16_t posY = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));

        // TileMap& tileMap = _infos.getTileMap(posX, posY); TODO
        // tileMap.setIncantation(true);
    }

    void Parser::endIncantation(std::string& secondString) {
        // pie X Y R\n
        uint16_t posX = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 0));
        uint16_t posY = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));
        int result = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 2));

//        TileMap& tileMap = _infos.getTileMap(posX, posY); TODO
//        tileMap.setIncantation(result);
    }

    void Parser::eggLaying(std::string& secondString) {
        // pfk n\n (temps de chargement de l'oeuf)
        int id = std::stoi(Utils::split(secondString, ' ', 1).first);
    }

    void Parser::getResourceDropping(std::string& secondString) {
//        // pdr n i\n TODO
//        int id = std::stoi(Utils::split(secondString, ' ', 1).first);
//        uint16_t resourceNumber = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));
//
//        std::shared_ptr<Player> player = _infos.getPlayer(id);
//        player.get()->removeQuantity(resourceNumber, 1);
//
//        auto [posX, posY] = player.get()->getPosition();
//        TileMap& tileMap = _infos.getTileMap(posX, posY);
//        tileMap.addQuantity(resourceNumber, 1);
    }

    void Parser::getResourceCollecting(std::string& secondString) {
//        // pgt n i\n TODO
//        int id = std::stoi(Utils::split(secondString, ' ', 1).first);
//        uint16_t resourceNumber = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 1));
//
//        std::shared_ptr<Player> player = _infos.getPlayer(id);
//        player.get()->addQuantity(resourceNumber, 1);
//
//        auto [posX, posY] = player.get()->getPosition();
//        TileMap& tileMap = _infos.getTileMap(posX, posY);
//        tileMap.removeQuantity(resourceNumber, 1);
    }

    void Parser::getDeathOfPlayer(std::string& secondString) {
        // pdi n\n
        int id = std::stoi(Utils::split(secondString, ' ', 1).first);
        _infos.removePlayer(id);
    }

    void Parser::eggCreation(std::string& secondString) {
        // enw e n X Y\n (l'oeuf apparait sur la map)
        // enw    1             0                0      0
        // enw <idEgg> <idPlayer toujours à 0> <posX> <posY>
        int idEgg = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 0));
        int idPlayer = 0;
        uint16_t posX = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 2));
        uint16_t posY = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 3));

        Egg egg(idEgg);
        egg.setPosition(posX, posY);
        _infos.addEgg(egg);
    }

    void Parser::playerConnectionForEgg(std::string& secondString) {
        // ebo e\n (l'oeuf éclot)
        int idEgg = std::stoi(Utils::getNumberAtIndex(secondString, ' ', 0));
        _infos.removeEgg(idEgg);
    }

    void Parser::getDeathOfEgg(std::string& secondString) {
        int idEgg = std::stoi(Utils::split(secondString, ' ', 1).first);
        _infos.removeEgg(idEgg);
    }

    void Parser::timeUnitRequest(std::string& secondString) {
        // sgt T\n
    }

    void Parser::timeUnitModification(std::string& secondString) {
        // sst T\n
    }

    void Parser::endOfGame(std::string& secondString) {
        std::cout << "End of game" << std::endl;
        // seg N\n
    }

    void Parser::messageFromServer(std::string& secondString) {
        // smg M\n (message from server)
    }

    void Parser::unknownCommand(std::string& secondString) {
        std::cout << "Unknown command" << std::endl;
        // suc\n
    }

    void Parser::badParameter(std::string& secondString) {
        std::cout << "Command parameter" << std::endl;
        // sbp\n
    }
} // zappy
