/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_mct
*/

#include "server.h"

void cmd_mct(server_t *serv, player_t *player, char *cmd)
{
    int *res;

    if (!compare(cmd, 1)) return to_send(player, SBP);
    for (int i = 0; i < serv->height; i++)
        for (int j = 0; j < serv->width; j++) {
            res = get_resources(serv->board[i][j]->items);
            to_send(player, BCT, j, i, res[0], res[1], res[2], res[3], res[4],
                res[5], res[6]);
            free(res);
        }
}
