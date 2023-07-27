/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** handle_resources
*/

#include "server.h"

void handle_resources(server_t *serv)
{
    if (!elapse(serv, serv->item_spawn, RESOURCES_CYCLE)) return;
    put_resources(serv);
    serv->item_spawn = clock();
}
