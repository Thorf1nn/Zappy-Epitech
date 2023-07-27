/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_end_incantation
*/

#include "server.h"

void create_task_cmd(player_t *player, exec func, int rdn)
{
    cl_t *cl;
    cmd_t *tmp = calloc(1, sizeof(cmd_t));
    char *cmd = calloc(20, sizeof(cmd_t));

    strcats(cmd, "$ican", itos(rdn));
    tmp->cmd = cmd;
    tmp->exec = func;
    tmp->cycle = func == cmd_end_incantation ? 300 : INT_MAX;
    tmp->start = clock();
    cl = new_cmd(tmp);
    cl->next = func == cmd_end_incantation ? player->to_exec->next : NULL;
    if (func == cmd_end_incantation)
        player->to_exec->next = cl;
    else
        player->to_exec = cl;
    to_send(player, "Elevation underway\n");
}

void empty_cmd(server_t *serv pass, player_t *player pass, char *cmd)
{
    if (!compare(cmd, 1)) return;
    return;
}

void incress_level(server_t *serv, player_t *player, player_t *tmp, bool valid)
{
    cmd_t *check = tmp->to_exec ? tmp->to_exec->data : NULL;

    if (!check) return;
    if (strcmp(check->cmd, player->to_exec->data->cmd) == 0) {
        if (valid) {
            tmp->level++;
            to_send(tmp, "Current level: %d\n", tmp->level);
            to_send(serv->graphical, PLV, tmp->id, tmp->level);
        }
        check->cycle = 0;
    }
}

void cmd_end_incantation(server_t *serv, player_t *player, char *cmd pass)
{
    bool valid = check_can(player, true, true);

    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next)
        incress_level(serv, player, tmp->data, valid);
    if (!valid) { to_send(player, STR_KO); }
}
