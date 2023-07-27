/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_bct
*/

#include "server.h"

void cmd_bct(server_t *serv, player_t *player, char *cmd)
{
    char **data;
    int *res;

    if (!compare(cmd, 3)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    res = get_resources(serv->board[atoi(data[1])][atoi(data[2])]->items);
    to_send(player, BCT, atoi(data[1]), atoi(data[2]), res[0], res[1], res[2],
        res[3], res[4], res[5], res[6]);
    free(res);
    free_arr(data);
}
