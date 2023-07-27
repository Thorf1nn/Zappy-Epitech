/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** register_graphic
*/

#include "server.h"

static const cmd_t CMDS[] = {
    {"msz", 0, cmd_msz, (clock_t) 0},
    {"bct", 0, cmd_bct, (clock_t) 0},
    {"mct", 0, cmd_mct, (clock_t) 0},
    {"tna", 0, cmd_tna, (clock_t) 0},
    {"ppo", 0, cmd_ppo, (clock_t) 0},
    {"plv", 0, cmd_plv, (clock_t) 0},
    {"pin", 0, cmd_pin, (clock_t) 0},
    {"sgt", 0, cmd_sgt, (clock_t) 0},
    {"sst", 0, cmd_sst, (clock_t) 0},
};

void register_graphic_fail(player_t *player)
{
    cmd_t *tmp = calloc(1, sizeof(cmd_t));

    tmp->cmd = strdup("suc");
    tmp->exec = cmd_suc;
    tmp->cycle = 0;
    tmp->start = clock();
    push_cmd(&player->to_exec, tmp);
}

void register_graphic_cmd(player_t *player, char **cmds, char **data, int i)
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
    register_graphic_fail(player);
}
