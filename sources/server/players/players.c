/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** players
*/

#include "server.h"

void delete_player(server_t *serv, pl_t **players)
{
    int id = (*players)->data->id;

    close((*players)->data->fd);
    if ((*players)->data->is_graphical) serv->graphical = NULL;
    if ((*players)->data->team) {
        del_pl(&(*players)->data->square->players, (*players)->data, false);
        clear_il(&(*players)->data->inventory);
    }
    free((*players)->data->buff);
    del_pl(&serv->players, (*players)->data, true);
    *players = serv->players;
    to_send(serv->graphical, PDI, id);
    return;
}

void player_join_team(server_t *serv, player_t *player, int team)
{
    player->life = clock();
    player->id = ++(serv->id_p);
    player->steps++;
    player->level = 1;
    player->team = serv->teams[team];
    player->dir = (dir_t) rand() % 4;
    spawn_player(serv, player);
    for (int j = 0; j < 10; j++, push_il(&player->inventory, FOOD)) {};
    push_pl(&player->square->players, player);
    return;
}

void new_player(server_t *serv, int fd)
{
    player_t *new_player = calloc(1, sizeof(player_t));

    new_player->fd = fd;
    new_player->s_buff = READ_SIZE + 1;
    new_player->buff = calloc(READ_SIZE + 1, sizeof(char));
    new_player->team = NULL;
    new_player->steps = 0;
    new_player->square = NULL;
    new_player->nb_cmd = 0;
    new_player->to_exec = NULL;
    new_player->to_send = NULL;
    new_player->dir = NO_DIR;
    new_player->disconnected = false;
    new_player->is_graphical = false;
    push_pl(&serv->players, new_player);
    to_send(new_player, STR_WELCOME);
    return;
}
