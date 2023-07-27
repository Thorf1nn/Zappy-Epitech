/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_forward
*/

#include "server.h"

void move_player(server_t *serv, player_t *player, int y, int x)
{
    player->y = (player->y + y) % serv->height;
    player->x = (player->x + x) % serv->width;
    if (player->y < 0) player->y = serv->height + player->y;
    if (player->x < 0) player->x = serv->width + player->x;
    del_pl(&player->square->players, player, false);
    player->square = serv->board[player->y][player->x];
    push_pl(&player->square->players, player);
}

void cmd_forward(server_t *serv, player_t *player, char *cmd)
{
    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    switch (player->dir) {
        case (UP): move_player(serv, player, -1, 0); break;
        case (RIGHT): move_player(serv, player, 0, 1); break;
        case (DOWN): move_player(serv, player, 1, 0); break;
        case (LEFT): move_player(serv, player, 0, -1); break;
        default: to_send(player, STR_KO); return;
    }
    to_send(player, STR_OK);
    to_send(serv->graphical, PPO, player->id, player->x, player->y,
        player->dir + 1);
}
