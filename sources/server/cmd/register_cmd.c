/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** register_cmd
*/

#include "server.h"

static const cmd_t CMDS[] = {
    {"Forward", 7, cmd_forward, (clock_t) 0},
    {"Left", 7, cmd_left, (clock_t) 0},
    {"Right", 7, cmd_right, (clock_t) 0},
    {"Look", 7, cmd_look, (clock_t) 0},
    {"Inventory", 1, cmd_inv, (clock_t) 0},
    {"Broadcast", 7, cmd_broadcast, (clock_t) 0},
    {"Connect_nbr", 0, cmd_connect, (clock_t) 0},
    {"Fork", 0, cmd_fork, (clock_t) 0},
    {"Eject", 7, cmd_eject, (clock_t) 0},
    {"Take", 7, cmd_take, (clock_t) 0},
    {"Set", 7, cmd_set, (clock_t) 0},
    {"Incantation", 0, cmd_incantation, (clock_t) 0},
};

void register_fail(player_t *player)
{
    cmd_t *tmp;
    tmp = calloc(1, sizeof(cmd_t));
    tmp->cmd = strdup("ko");
    tmp->exec = cmd_ko;
    tmp->cycle = 0;
    tmp->start = clock();
    push_cmd(&player->to_exec, tmp);
}

void register_cmd(player_t *player, char **cmds, char **data, int i)
{
    cmd_t *tmp;

    for (int j = 0; j < 12; j++) {
        if (strcmp(data[0], CMDS[j].cmd) != 0) continue;
        tmp = calloc(1, sizeof(cmd_t));
        tmp->cmd = strdup(cmds[i]);
        tmp->exec = CMDS[j].exec;
        tmp->cycle = CMDS[j].cycle;
        tmp->start = clock();
        push_cmd(&player->to_exec, tmp);
        return;
    }
    register_fail(player);
}
