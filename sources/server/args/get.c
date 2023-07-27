/*
** EPITECH PROJECT, 2023
** zappy [WSL: Ubuntu]
** File description:
** get
*/

#include "server.h"

void init_global_struct(server_t *serv)
{
    serv->id_p = 0;
    serv->id_e = 0;
    serv->freq = 100;
    serv->width = 10;
    serv->height = 10;
    serv->port = 4242;
    serv->clients_nb = 3;
    serv->item_spawn = 0;
    serv->net = NULL;
    serv->eggs = NULL;
    serv->board = NULL;
    serv->teams = NULL;
    serv->players = NULL;
    serv->graphical = NULL;
}

int get_args(server_t *serv, int ac, char **av)
{
    init_global_struct(serv);
    for (int i = 1; i < ac; i++)
        if (!check_args(serv, i, av)) return false;
    if (!serv->port || !serv->freq || !serv->clients_nb)
        return print_usage_error("Port, freq & clientsNb must be > 0", false);
    if (serv->width > 30 || serv->height > 30 || serv->width < 10
        || serv->height < 10)
        return print_usage_error("10 <= Width & height <= 30", false);
    if (serv->freq < 2 || serv->freq > 10000)
        return print_usage_error("2 <= freq <= 10000", false);
    default_team(serv);
    return true;
}
