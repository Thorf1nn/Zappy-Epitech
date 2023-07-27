/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_fork
*/

#include "server.h"

void cmd_fork(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    spawn_eggs(serv, NULL, player);
    to_send(player, STR_OK);
    to_send(serv->graphical, PFK, player->id);
}
