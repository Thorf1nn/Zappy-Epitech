/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_incantation
*/

#include "server.h"

bool check_player(player_t *player, int level, int need, bool after)
{
    int nb = 0;
    cmd_t *check;
    bool test;

    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next) {
        check = tmp->data->to_exec ? tmp->data->to_exec->data : NULL;
        test = check ? check->cmd[0] != '$' : true;
        if (tmp->data->level == level && (test || after)) nb++;
    }
    return nb >= need;
}

bool check_resources(player_t *player, int need[7])
{
    int *res = get_resources(player->square->items);

    for (int i = 1; i < 6; i++)
        if (res[i] < need[i]) return false;
    return true;
}

bool check_can(player_t *pl, bool remove, bool after)
{
    int need[7][7] = {{1, 1, 0, 0, 0, 0, 0}, {2, 1, 1, 1, 0, 0, 0},
        {2, 2, 0, 1, 0, 2, 0}, {4, 1, 1, 2, 0, 1, 0}, {4, 1, 2, 1, 3, 0, 0},
        {6, 1, 2, 3, 0, 1, 0}, {6, 2, 2, 2, 2, 2, 1}};

    if (!check_player(pl, pl->level, need[pl->level - 1][0], after))
        return false;
    if (!check_resources(pl, need[pl->level - 1])) return false;
    if (!remove) return true;
    for (int i = 1; i < 6; i++)
        for (int j = 0; j < need[pl->level - 1][i]; j++)
            del_il(&pl->square->items, i);
    return true;
}

void cmd_incantation(server_t *serv pass, player_t *player, char *cmd)
{
    int rdn = rand() % 100;
    cmd_t *check;
    bool test;

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    if (!check_can(player, false, false)) return to_send(player, STR_KO);
    for (pl_t *tmp = player->square->players; tmp; tmp = tmp->next) {
        check = tmp->data->to_exec ? tmp->data->to_exec->data : NULL;
        test = check ? check->cmd[0] != '$' : true;
        if (tmp->data->level == player->level && tmp->data != player && test)
            create_task_cmd(tmp->data, empty_cmd, rdn);
    }
    create_task_cmd(player, cmd_end_incantation, rdn);
}
