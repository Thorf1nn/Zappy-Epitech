/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_ko
*/

#include "server.h"

void cmd_ko(server_t *serv pass, player_t *player, char *cmd pass)
{
    to_send(player, STR_KO);
}
