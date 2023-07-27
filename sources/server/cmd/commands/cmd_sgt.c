/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_sgt
*/

#include "server.h"

void cmd_sgt(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    if (!compare(cmd, 1)) return to_send(player, SBP);
    to_send(player, SGT, serv->freq);
}
