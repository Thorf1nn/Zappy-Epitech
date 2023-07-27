/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** team
*/

#include "server.h"

void join_step(server_t *serv, player_t *player)
{
    char *data = player->buff;
    team_t *team;

    data[strlen(data) - 1] = '\0';
    if (strcmp(data, "GRAPHIC") == 0)
        return add_player_to_graphic(serv, player);
    for (int i = 0; (team = serv->teams[i]); i++)
        if (!strcmp(data, team->name) && slot_available(serv, team) > 0)
            return add_player_to_team(serv, player, i);
    to_send(player, STR_KO);
    return;
}

void cmd_step(server_t *serv pass, player_t *player)
{
    char **cmds = strarr(player->buff, "\n");
    char **data;

    if (!cmds || !*cmds) return;
    for (int i = 0; cmds[i]; i++) {
        if (len_cmd(player->to_exec) >= 10) continue;
        data = strarr(cmds[i], " ");
        if (!data || !*data) continue;
        if (player->is_graphical)
            register_graphic_cmd(player, cmds, data, i);
        else
            register_cmd(player, cmds, data, i);
        free_arr(data);
    }
    free_arr(cmds);
}

void call_step(server_t *serv, player_t *player)
{
    step_function_ptr funcs[] = {join_step, cmd_step};

    if (player->steps == -1) return;
    funcs[player->steps](serv, player);
    memset(player->buff, 0, player->s_buff);
    player->nb_cmd = 0;
}
