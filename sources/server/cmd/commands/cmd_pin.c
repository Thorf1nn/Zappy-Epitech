/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_pin
*/

#include "server.h"

void cmd_pin(server_t *serv, player_t *player, char *cmd)
{
    char **data;
    player_t *tmp = NULL;
    int *inv;

    if (!compare(cmd, 2)) return to_send(player, SBP);
    data = strarr(cmd, " ");
    for (pl_t *pls = serv->players; pls; pls = pls->next)
        if (pls->data->id == atoi(data[1])) tmp = pls->data;
    if (!tmp) return to_send(player, SBP);
    inv = get_resources(tmp->inventory);
    to_send(player, PIN, tmp->id, tmp->x, tmp->y, inv[0], inv[1], inv[2],
        inv[3], inv[4], inv[5], inv[6]);
    free(inv);
    free_arr(data);
}
