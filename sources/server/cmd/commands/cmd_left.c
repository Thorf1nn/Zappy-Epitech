/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_left
*/

#include "server.h"

void cmd_left(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    player->dir = (dir_t) ((player->dir - 1) % 4);
    to_send(player, STR_OK);
    to_send(serv->graphical, PPO, player->id, player->x, player->y,
        player->dir + 1);
}
