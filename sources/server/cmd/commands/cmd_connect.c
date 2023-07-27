/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_connect
*/

#include "server.h"

void cmd_connect(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    to_send(player, "%d\n", slot_available(serv, player->team));
}
