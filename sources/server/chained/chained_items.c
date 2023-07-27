/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** chained_items
*/

#include "server.h"

il_t *new_il(item_t data)
{
    il_t *il = calloc(1, sizeof(il_t));

    il->data = data;
    il->next = NULL;
    return il;
}

void push_il(il_t **ils, item_t data)
{
    il_t *il = *ils;
    il_t *tmp = il;

    if (!il) {
        *ils = new_il(data);
        return;
    }
    for (; tmp->next;) tmp = tmp->next;
    tmp->next = new_il(data);
}

void clear_il(il_t **ils)
{
    for (il_t *tmp_free, *tmp = (*ils); (tmp_free = tmp);) {
        tmp = tmp->next;
        if (tmp_free) free(tmp_free);
    }
    (*ils) = NULL;
}

void del_il(il_t **ils, item_t data)
{
    il_t *tmp = *ils;
    il_t *prev = NULL;

    for (; tmp && tmp->data != data; tmp = tmp->next) prev = tmp;
    if (!tmp) return;
    if (prev)
        prev->next = tmp->next;
    else
        *ils = tmp->next;
    free(tmp);
}

int len_il(il_t *il)
{
    int size = 0;

    for (il_t *tmp = il; tmp; tmp = tmp->next) size++;
    return size;
}
