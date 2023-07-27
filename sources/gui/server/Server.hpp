/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** Server
*/

#ifndef Server_HPP_
#define Server_HPP_

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>

#include "Utils.hpp"
#include "Parser.hpp"
#include "ServerException.hpp"

#define BUFFER_SIZE 32768

namespace zappy {
    class Server {
    public:
        Server() = default;
        Server(int port, std::string machine);
        ~Server();

        void setPort(int port);
        void setMachine(std::string machine);
        void create();
        void connect();
        void receive();
        void send();
        void send(const std::string& message);
        void close();

        Parser getParser() const;

    private:
        int _port;
        std::string _machine;

        int _socketFd;
        int _nbLoop;
        struct sockaddr_in _serverAddress;
        struct sockaddr_in _clientAddress;

        Parser _parser;
    };
}

#endif /* Server_HPP_ */
