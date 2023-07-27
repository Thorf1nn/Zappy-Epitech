/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_suc
*/

#include "server.h"

void cmd_suc(server_t *serv pass, player_t *player, char *cmd pass)
{
    to_send(player, SUC);
}
