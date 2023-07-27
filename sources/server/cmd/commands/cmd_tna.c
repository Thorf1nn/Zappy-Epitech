/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_tna
*/

#include "server.h"

void cmd_tna(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, SBP);
    for (int i = 0; serv->teams[i]; i++)
        to_send(player, TNA, serv->teams[i]->name);
}
