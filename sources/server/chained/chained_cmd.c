/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** chained
*/

#include "server.h"

cl_t *new_cmd(cmd_t *cmd)
{
    cl_t *cmd_new = calloc(1, sizeof(cl_t));

    cmd_new->data = cmd;
    cmd_new->next = NULL;
    return cmd_new;
}

void push_cmd(cl_t **cmds, cmd_t *data)
{
    cl_t *cmd = *cmds;
    cl_t *tmp = cmd;

    if (!cmd) {
        *cmds = (cl_t *) new_cmd(data);
        return;
    }
    for (; tmp->next;) tmp = tmp->next;
    tmp->next = (cl_t *) new_cmd(data);
}

void clear_cmd(cl_t **cmds)
{
    cl_t *cmd = *cmds;
    cl_t *tmp = cmd;
    cl_t *tmp_free = NULL;

    for (; tmp; tmp = tmp_free) {
        tmp_free = tmp->next;
        free(tmp->data);
        free(tmp);
    }
    *cmds = NULL;
}

void del_cmd(cl_t **cmds, cmd_t *data, bool free_p)
{
    cl_t *cmd = *cmds;
    cl_t *prev = NULL;

    for (; cmd && cmd->data != data; cmd = cmd->next) prev = cmd;
    if (!cmd) return;
    if (prev)
        prev->next = cmd->next;
    else
        *cmds = cmd->next;
    if (free_p) free(cmd->data);
    free(cmd);
}

int len_cmd(cl_t *cmd)
{
    int i = 0;

    for (cl_t *tmp = cmd; tmp; tmp = tmp->next) i++;
    return i;
}
