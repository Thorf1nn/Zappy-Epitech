/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** loop_server
*/

#include "server.h"

bool main_server(server_t *serv)
{
    fill_select(serv);
    if (!fd_select(serv)) return false;
    handle_select(serv);
    handle_cmd(serv);
    handle_life(serv);
    handle_eggs(serv);
    handle_resources(serv);
    return true;
}

bool loop_server(server_t *serv)
{
    bool succ_loop;

    printf("Port : %d\n", serv->port);
    while (1) {
        succ_loop = main_server(serv);
        if (!succ_loop) return false;
    }
    return true;
}
