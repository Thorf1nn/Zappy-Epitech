/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_msz
*/

#include "server.h"

void cmd_msz(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, SBP);
    to_send(player, MSZ, serv->width, serv->height);
}
