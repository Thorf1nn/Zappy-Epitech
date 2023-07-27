/*
** EPITECH PROJECT, 2023
** zappy [WSL: Ubuntu]
** File description:
** send_board
*/

#include "server.h"

void send_buff(player_t *graphic, char *buff)
{
    to_send(graphic, buff);
    memset(buff, 0, READ_SIZE + 1);
}

void send_board(server_t *serv, player_t *graphic)
{
    int *res;
    to_send(graphic, MSZ, serv->width, serv->height);
    to_send(graphic, SGT, serv->freq);
    for (int i = 0; i < serv->height; i++)
        for (int j = 0; j < serv->width; j++) {
            res = get_resources(serv->board[i][j]->items);
            to_send(graphic, BCT, j, i, res[0], res[1], res[2], res[3], res[4],
                res[5], res[6]);
            free(res);
        }
    for (int i = 0; serv->teams[i]; i++)
        to_send(graphic, TNA, serv->teams[i]->name);
    for (pl_t *tmp = serv->players; tmp; tmp = tmp->next)
        if (!tmp->data->is_graphical && tmp->data->team)
            to_send(graphic, PNW, tmp->data->id, tmp->data->x, tmp->data->y,
                tmp->data->dir + 1, tmp->data->level, tmp->data->team->name);
    for (el_t *tmp = serv->eggs; tmp; tmp = tmp->next)
        to_send(graphic, ENW, tmp->data->id, tmp->data->pid,
            tmp->data->square->pos.x, tmp->data->square->pos.y);
}
