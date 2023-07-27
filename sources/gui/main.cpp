/*
** EPITECH PROJECT, 2023
** B-YEP-400-MPL-4-1-zappy-hugo.eschlimann
** File description:
** main
*/

#include "core/Core.hpp"

int main(int ac, char **av) {
    SetTraceLogCallback([](int, const char *, va_list) {});
    if (ac == 2 && std::string(av[1]) == "-help") {
        std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
        std::cout << "       port     is the port number" << std::endl;
        std::cout << "       machine  is the name of the machine; localhost by default" << std::endl;
        return EXIT_SUCCESS;
    }
    if (ac < 3) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 84;
    }

    try {
        int port = std::stoi(av[2]);
        std::string machine;
        if (ac == 3) {
            machine = LOCALHOST;
        } else {
            machine = av[4];
        }
        zappy::Core core(port, machine);
        core.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
