/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_broadcast
*/

#include "server.h"

static const ori_t ORI[] = {{UP, 2, 1, 8, 4, 5, 6, 3, 7},
    {RIGHT, 4, 3, 2, 6, 7, 8, 5, 1}, {DOWN, 6, 5, 4, 8, 1, 2, 7, 3},
    {LEFT, 8, 7, 6, 2, 3, 4, 1, 5}, {NO_DIR, 0, 0, 0, 0, 0, 0, 0, 0}};

int adapt_orientation(dir_t dir, int ori, int i)
{
    while (ORI[++i].dir != dir);
    switch (ori) {
        case (11): return (ORI[i].up_left);
        case (21): return (ORI[i].down_left);
        case (31): return (ORI[i].center_left);
        case (12): return (ORI[i].up_right);
        case (22): return (ORI[i].down_right);
        case (32): return (ORI[i].center_right);
        case (13): return (ORI[i].up_center);
        case (23): return (ORI[i].down_center);
        default: return (0);
    }
}

vec_t get_distance(server_t *serv, player_t *from, player_t *to)
{
    bool bx = abs(serv->width - abs(to->x - from->x)) < abs(to->x - from->x);
    bool by = abs(serv->height - abs(to->y - from->y)) < abs(to->y - from->y);
    int x = from->x < to->x ? 1 : from->x > to->x ? -1 : 0;
    int y = from->y < to->y ? 1 : from->y > to->y ? -1 : 0;

    return (vec_t){x * (bx ? -1 : 1), y * (by ? -1 : 1)};
}

int get_orientation(server_t *serv, player_t *from, player_t *to)
{
    vec_t dist = get_distance(serv, from, to);
    int ori = 0;

    if (to->square == from->square) return 0;
    ori += dist.x == 1 ? 1 : dist.x == -1 ? 2 : 3;
    ori += dist.y == 1 ? 10 : dist.y == -1 ? 20 : 30;
    return adapt_orientation(to->dir, ori, -1);
}

void cmd_broadcast(server_t *serv, player_t *player pass, char *cmd)
{
    pl_t *to = serv->players;
    int ori;
    char **av;

    if (!compare(cmd, 2)) return to_send(player, STR_KO);
    av = strarr(cmd, " ");
    for (; to; to = to->next) {
        if (to->data == player || !to->data->team) continue;
        ori = get_orientation(serv, player, to->data);
        to_send(to->data, "message %d, %s\n", ori, av[1]);
    }
    to_send(player, STR_OK);
    to_send(serv->graphical, PBC, player->id, av[1]);
    free_arr(av);
}
