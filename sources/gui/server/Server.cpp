#include "Server.hpp"

namespace zappy {
    Server::Server(int port, std::string machine)
            : _port(port), _machine(machine), _socketFd(0) {
    }

    void Server::create() {
        _socketFd = socket(AF_INET, SOCK_STREAM, 0);
        if (_socketFd == -1) {
            std::cerr << "Could not create socket" << std::endl;
        }
        std::cout << "Socket created" << std::endl;
        std::fill(reinterpret_cast<char*>(&_serverAddress), reinterpret_cast<char*>(&_serverAddress) + sizeof(_serverAddress), 0);

        _serverAddress.sin_family = AF_INET;
        _serverAddress.sin_addr.s_addr = Utils::inetAddr(_machine.c_str());
        _serverAddress.sin_port = Utils::htons(_port);
    }

    void Server::connect() {
        if (::connect(_socketFd, (struct sockaddr *)&_serverAddress, sizeof(_serverAddress)) < 0) {
            std::cerr << "Could not connect to server" << std::endl;
        }
        std::cout << "Connected" << std::endl;
    }

    void Server::receive() {
        std::vector<char> buffer(BUFFER_SIZE);
        std::string line;
        struct timeval timeout;
        fd_set readSet;

        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        FD_ZERO(&readSet);
        FD_SET(_socketFd, &readSet);

        if (select(FD_SETSIZE, &readSet, nullptr, nullptr, &timeout) < 0) {
            throw std::runtime_error("Select error");
        }
        if (FD_ISSET(_socketFd, &readSet)) {
            size_t bytesRecv = recv(_socketFd, buffer.data(), BUFFER_SIZE, 0);
            if (static_cast<int>(bytesRecv) == -1) {
                throw ServerException("Server.cpp 42: recv error");
            }

            for (size_t i = 0; i < bytesRecv; i++) {
                char ch = buffer[i];
                if (ch == '\n') {
                    _parser.getCommands(line);
                    line.clear();
                } else {
                    line += ch;
                }
            }
        }
        buffer.clear();
    }

    void Server::send() {
        char buffer[1024];
        fd_set writeSet;
        struct timeval timeout;

        timeout.tv_sec = 0;
        timeout.tv_usec = 0;

        FD_ZERO(&writeSet);
        FD_SET(_socketFd, &writeSet);

        if (select(_socketFd + 1, nullptr, &writeSet, nullptr, &timeout) < 0) {
            throw ServerException("Server.cpp 68: select error");
        }
        if (FD_ISSET(_socketFd, &writeSet)) {
            std::cin.getline(buffer, sizeof(buffer));
            if (write(_socketFd, buffer, sizeof(buffer)) < 0) {
                throw ServerException("Server.cpp 73: write error");
            }
        }
    }

    void Server::send(const std::string& message) {
        if (::send(_socketFd, message.c_str(), message.size(), 0) < 0) {
            throw ServerException("Server.cpp 80: send error");
        }
    }

    void Server::close() {
        if (::close(_socketFd) < 0) {
            throw ServerException("Server.cpp 86: close error");
        }
    }

    void Server::setPort(int port) {
        _port = port;
    }

    void Server::setMachine(std::string machine) {
        _machine = machine;
    }

    Parser Server::getParser() const {
        return _parser;
    }

    Server::~Server() {
    }
}