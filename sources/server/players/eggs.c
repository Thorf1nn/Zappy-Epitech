/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** eggs
*/

#include "server.h"

void spawn_eggs(server_t *serv, team_t *team, player_t *player)
{
    egg_t *egg = calloc(1, sizeof(egg_t));
    square_t *square =
        serv->board[rand() % serv->width][rand() % serv->height];

    egg->square = player ? player->square : square;
    egg->team = player ? player->team : team;
    egg->pid = player ? player->id : 0;
    egg->cycle = player ? clock() : 0;
    egg->id = ++serv->id_e;
    push_el(&serv->eggs, egg);
}

void create_eggs(server_t *serv)
{
    for (int i = 0; serv->teams[i]; i++)
        for (int j = 0; j < serv->clients_nb; j++)
            spawn_eggs(serv, serv->teams[i], NULL);
}

egg_t *get_egg(server_t *serv, team_t *team)
{
    for (el_t *tmp = serv->eggs; tmp; tmp = tmp->next)
        if (tmp->data->team == team && !tmp->data->cycle) return tmp->data;
    return NULL;
}

void spawn_player(server_t *serv, player_t *player)
{
    egg_t *egg = get_egg(serv, player->team);

    if (!egg) return;
    player->square = egg->square;
    player->x = egg->square->pos.x;
    player->y = egg->square->pos.y;
    to_send(serv->graphical, EBO, egg->id);
    del_el(&serv->eggs, egg, true);
}
