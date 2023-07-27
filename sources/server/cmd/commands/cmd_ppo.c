/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_ppo
*/

#include "server.h"

void cmd_ppo(server_t *serv pass, player_t *player pass, char *cmd pass)
{
    char **data;
    player_t *tmp = NULL;

    if (!compare(cmd, 2)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    for (pl_t *pls = serv->players; pls; pls = pls->next)
        if (pls->data->id == atoi(data[1])) tmp = pls->data;
    if (!tmp) return to_send(player, SBP);
    to_send(player, PPO, tmp->id, tmp->x, tmp->y, tmp->dir);
    free_arr(data);
}
