/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_sst
*/

#include "server.h"

void cmd_sst(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    char **data;
    int freq;

    if (!compare(cmd, 2)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    freq = atoi(data[1]);
    if (freq < 2) return to_send(player, SBP);
    serv->freq = freq;
    to_send(player, SST, serv->freq);
    free_arr(data);
}
