/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** chained
*/

#include "server.h"

ml_t *new_msg(char *msg)
{
    ml_t *msg_new = calloc(1, sizeof(ml_t));

    msg_new->data = msg;
    msg_new->next = NULL;
    return msg_new;
}

void push_msg(ml_t **msgs, char *data)
{
    ml_t *msg = *msgs;
    ml_t *tmp = msg;

    if (!msg) {
        *msgs = (ml_t *) new_msg(data);
        return;
    }
    for (; tmp->next;) tmp = tmp->next;
    tmp->next = (ml_t *) new_msg(data);
}

void clear_msg(ml_t **msgs)
{
    ml_t *msg = *msgs;
    ml_t *tmp = msg;
    ml_t *tmp_free = NULL;

    for (; tmp; tmp = tmp_free) {
        tmp_free = tmp->next;
        free(tmp->data);
        free(tmp);
    }
    *msgs = NULL;
}

int len_msg(ml_t *msg)
{
    int i = 0;

    for (ml_t *tmp = msg; tmp && tmp->data; tmp = tmp->next) i++;
    return i;
}
