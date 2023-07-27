/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_look
*/

#include "server.h"

char *item_name(item_t item)
{
    char *name[8] = {"food", "linemate", "deraumere", "sibur", "mendiane",
        "phiras", "thystame", "player"};

    return name[(int) item];
}

void square_to_str(square_t *square, char *buff)
{
    for (il_t *tmp = square->items; tmp; tmp = tmp->next)
        strcats(buff, " ", item_name(tmp->data), NULL);
}

square_t *get_square(server_t *serv, player_t *pl, int i, int j)
{
    int pos[4][2] = {{-i, j}, {j, i}, {i, -j}, {-j, -i}};
    int p[2] = {pl->y + pos[pl->dir][0], pl->x + pos[pl->dir][1]};
    int x = p[1] < 0 ? p[1] + serv->width : (p[1] % serv->width);
    int y = p[0] < 0 ? p[0] + serv->height : (p[0] % serv->height);

    return serv->board[y][x];
}

void get_content(server_t *serv, player_t *player, char *buff, int idxs[2])
{
    square_t *square = get_square(serv, player, idxs[0], idxs[1]);
    int nb_players = len_pl(square->players);

    for (int i = 0; i < nb_players; i++) strcats(buff, " player", NULL);
    if (len_il(square->items) > 0) square_to_str(square, buff);
    if (idxs[0] != player->level || idxs[1] != idxs[0] * 2)
        strcats(buff, ",", NULL);
}

void cmd_look(server_t *serv, player_t *player, char *cmd)
{
    char *buff;
    int idxs[2] = {0, 0};

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    buff = calloc(READ_SIZE, sizeof(char));
    strcats(buff, "[", NULL);
    for (idxs[0] = 0; idxs[0] <= player->level; idxs[0]++)
        for (idxs[1] = -idxs[0]; idxs[1] <= idxs[0]; idxs[1]++)
            get_content(serv, player, buff, idxs);
    strcats(buff, " ]\n", NULL);
    to_send(player, buff);
    free(buff);
}
