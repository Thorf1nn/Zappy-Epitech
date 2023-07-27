/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** handle_life
*/

#include "server.h"

void eat(server_t *serv pass, player_t *player)
{
    int food = getter_resource(player->inventory, FOOD);

    if (food > 0) {
        player->life = clock();
        return del_il(&player->inventory, FOOD);
    }
    to_send(player, "dead\n");
    player->disconnected = true;
}

void handle_life(server_t *serv)
{
    for (pl_t *pl = serv->players; pl; pl = pl->next) {
        if (pl->data->disconnected || !pl->data->team) continue;
        if (!elapse(serv, pl->data->life, LIFE_CYCLE)) continue;
        eat(serv, pl->data);
    }
}
