/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** init_maps
*/

#include "server.h"

int board_resources(server_t *serv, item_t item)
{
    int count = 0;

    for (int y = 0, x = 0; y < serv->height; y++)
        for (x = 0; x < serv->width; x++)
            count += getter_resource(serv->board[y][x]->items, item);
    return count;
}

int max_resources(server_t *serv, item_t item)
{
    float densities[] = {FOOD_DENSITY, LINEMATE_DENSITY, DERAUMERE_DENSITY,
        SIBUR_DENSITY, MENDIANE_DENSITY, PHIRAS_DENSITY, THYSTAME_DENSITY};

    return (int) (serv->width * serv->height * densities[item]);
}

void put_resources(server_t *serv)
{
    int quantity = 0;
    int x;
    int y;

    for (item_t item = 0; item < 7; item++) {
        quantity = max_resources(serv, item) - board_resources(serv, item);
        while (0 < quantity) {
            x = rand() % serv->width;
            y = rand() % serv->height;
            push_il(&serv->board[y][x]->items, item);
            quantity--;
        }
    }
}

void build_board(server_t *serv)
{
    serv->board = calloc(serv->height + 1, sizeof(square_t *));
    for (int y = 0, x = 0; y < serv->height; y++) {
        serv->board[y] = calloc(serv->width + 1, sizeof(square_t));
        for (x = 0; x < serv->width; x++) {
            serv->board[y][x] = calloc(1, sizeof(square_t));
            serv->board[y][x]->pos = (vec_t){x, y};
            serv->board[y][x]->players = NULL;
            serv->board[y][x]->items = NULL;
        }
        serv->board[y][serv->width] = NULL;
    }
    serv->board[serv->height] = NULL;
}
