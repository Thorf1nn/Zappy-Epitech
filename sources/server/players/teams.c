/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** teams
*/

#include "server.h"

void default_team(server_t *serv)
{
    char *buff[4] = {"Team1", "Team2", "Team3", "Team4"};

    if (serv->teams) return;
    serv->teams = calloc(5, sizeof(team_t *));
    for (int i = 0; i < 4; i++) {
        serv->teams[i] = calloc(1, sizeof(team_t));
        serv->teams[i]->name = strdup(buff[i]);
    }
}

int slot_available(server_t *serv, team_t *team)
{
    int nb = 0;

    for (el_t *tmp = serv->eggs; tmp; tmp = tmp->next)
        if (tmp->data->team == team && !tmp->data->cycle) nb++;
    return nb;
}

void add_player_to_team(server_t *serv, player_t *player, int team)
{
    int slot = slot_available(serv, serv->teams[team]);

    player_join_team(serv, player, team);
    to_send(player, "%d\n", slot - 1);
    to_send(player, "%d %d\n", serv->width, serv->height);
    to_send(serv->graphical, PNW, player->id, player->x, player->y,
        player->dir + 1, player->level, player->team->name);
}

void add_player_to_graphic(server_t *serv, player_t *player)
{
    player->id = 0;
    player->is_graphical = true;
    player->steps = 1;
    serv->graphical = player;
    send_board(serv, player);
}
