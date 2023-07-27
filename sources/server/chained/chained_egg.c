/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** chained_egg
*/

#include "server.h"

el_t *new_el(egg_t *data)
{
    el_t *el = calloc(1, sizeof(el_t));

    el->data = data;
    el->next = NULL;
    return el;
}

void push_el(el_t **els, egg_t *data)
{
    el_t *el = *els;
    el_t *tmp = el;

    if (!el) {
        *els = new_el(data);
        return;
    }
    for (; tmp->next;) tmp = tmp->next;
    tmp->next = new_el(data);
}

void clear_el(el_t **els, bool free_p)
{
    for (el_t *tmp_free, *tmp = (*els); (tmp_free = tmp);) {
        tmp = tmp->next;
        if (free_p) free(tmp_free->data);
        if (tmp_free) free(tmp_free);
    }
    (*els) = NULL;
}

void del_el(el_t **els, egg_t *data, bool free_p)
{
    el_t *tmp = *els;
    el_t *prev = NULL;

    for (; tmp && tmp->data != data; tmp = tmp->next) prev = tmp;
    if (!tmp) return;
    if (prev)
        prev->next = tmp->next;
    else
        *els = tmp->next;
    if (free_p) free(tmp->data);
    free(tmp);
}

int len_el(el_t *el)
{
    int size = 0;

    for (; el; el = el->next) size++;
    return size;
}
