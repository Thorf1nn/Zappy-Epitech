/*
** EPITECH PROJECT, 2023
** zappy [WSL: Ubuntu]
** File description:
** get_resource
*/

#include "server.h"

int *get_resources(il_t *items)
{
    int *resources = calloc(7, sizeof(int));

    resources[0] = getter_resource(items, FOOD);
    resources[1] = getter_resource(items, LINEMATE);
    resources[2] = getter_resource(items, DERAUMERE);
    resources[3] = getter_resource(items, SIBUR);
    resources[4] = getter_resource(items, MENDIANE);
    resources[5] = getter_resource(items, PHIRAS);
    resources[6] = getter_resource(items, THYSTAME);
    return resources;
}

int getter_resource(il_t *items, item_t item)
{
    int count = 0;

    for (il_t *tmp = items; tmp; tmp = tmp->next)
        if (tmp->data == item) count++;
    return count;
}
