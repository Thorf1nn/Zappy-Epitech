/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** handle_eggs
*/

#include "server.h"

void handle_eggs(server_t *serv)
{
    egg_t *egg;

    for (el_t *tmp = serv->eggs; tmp; tmp = tmp->next) {
        egg = tmp->data;
        if (!egg->cycle) continue;
        if (!elapse(serv, egg->cycle, EGG_CYCLE)) continue;
        egg->cycle = 0;
        to_send(serv->graphical, ENW, egg->id, egg->pid, egg->square->pos.x,
            egg->square->pos.y);
    }
}
