/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** handle_cmd
*/

#include "server.h"

bool execute_failed(server_t *serv, player_t *player)
{
    cl_t *next = NULL;
    for (cl_t *tmp = player->to_exec; tmp; tmp = next) {
        next = tmp->next;
        if (tmp->data->exec != cmd_ko) continue;
        tmp->data->exec(serv, player, tmp->data->cmd);
        free(tmp->data->cmd);
        del_cmd(&player->to_exec, tmp->data, true);
        if (player->to_exec) player->to_exec->data->start = clock();
    }
    return !player->to_exec;
}

void execute_action(server_t *serv, player_t *player)
{
    cmd_t *to_exec;

    if (execute_failed(serv, player)) return;
    to_exec = player->to_exec->data;
    if (!elapse(serv, to_exec->start, to_exec->cycle)) return;
    to_exec->exec(serv, player, to_exec->cmd);
    player->to_exec = player->to_exec->next;
    if (player->to_exec) player->to_exec->data->start = clock();
    free(to_exec->cmd);
    free(to_exec);
}

void handle_cmd(server_t *serv)
{
    for (pl_t *tmp = serv->players; tmp; tmp = tmp ? tmp->next : NULL) {
        if (tmp->data->disconnected) delete_player(serv, &tmp);
        if (tmp && tmp->data->nb_cmd) call_step(serv, tmp->data);
        if (tmp && tmp->data->to_exec) execute_action(serv, tmp->data);
    }
}
