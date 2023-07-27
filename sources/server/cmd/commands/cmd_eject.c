/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_eject
*/

#include "server.h"

void eject(server_t *serv, player_t *to, dir_t dir)
{
    int d[7][5] = {{5, 3, 1, 7, 0}, {1, 7, 5, 3, 0}, {3, 5, 7, 1, 0},
        {7, 1, 3, 5, 0}, {0, 0, 0, 0, 0}, {-1, 0, 1, 0, 0}, {0, 1, 0, -1, 0}};

    move_player(serv, to, d[5][dir], d[6][dir]);
    to_send(to, "eject: %d\n", d[to->dir][dir]);
    to_send(serv->graphical, PPO, to->id, to->x, to->y, to->dir + 1);
}

void cmd_eject(server_t *serv, player_t *player, char *cmd)
{
    bool ko = true;

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next) {
        if (tmp->data == player) continue;
        eject(serv, tmp->data, player->dir);
        ko = false;
    }
    for (el_t *tmp = serv->eggs; tmp; tmp = tmp->next) {
        if (tmp->data->square != player->square) continue;
        to_send(serv->graphical, EDI, tmp->data->id);
        del_el(&serv->eggs, tmp->data, true);
        ko = false;
    }
    to_send(player, ko ? STR_KO : STR_OK);
    if (!ko) to_send(serv->graphical, PEX, player->id);
}
