/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** chained_players
*/

#include "server.h"

pl_t *new_pl(player_t *data)
{
    pl_t *pl = calloc(1, sizeof(pl_t));

    pl->data = data;
    pl->next = NULL;
    return pl;
}

void push_pl(pl_t **pls, player_t *data)
{
    pl_t *pl = *pls;
    pl_t *tmp = pl;

    if (!pl) {
        *pls = new_pl(data);
        return;
    }
    for (; tmp->next;) tmp = tmp->next;
    tmp->next = new_pl(data);
}

void clear_pl(pl_t **pls, bool free_p)
{
    for (pl_t *tmp_free, *tmp = (*pls); (tmp_free = tmp);) {
        tmp = tmp->next;
        if (free_p) free(tmp_free->data);
        if (tmp_free) free(tmp_free);
    }
    (*pls) = NULL;
}

void del_pl(pl_t **pls, player_t *data, bool free_p)
{
    pl_t *tmp = *pls;
    pl_t *prev = NULL;

    for (; tmp && tmp->data != data; tmp = tmp->next) prev = tmp;
    if (!tmp) return;
    if (prev)
        prev->next = tmp->next;
    else
        *pls = tmp->next;
    if (free_p) free(tmp->data);
    free(tmp);
}

int len_pl(pl_t *pl)
{
    int size = 0;

    for (pl_t *tmp = pl; tmp; tmp = tmp->next) size++;
    return size;
}
