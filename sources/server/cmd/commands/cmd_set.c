/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_set
*/

#include "server.h"

void cmd_set(server_t *serv, player_t *player, char *cmd)
{
    char **tab;
    item_t data;

    if (!compare(cmd, 2)) return to_send(player, STR_KO);
    tab = strarr(cmd, " ");
    for (il_t *items = player->inventory; items; items = items->next) {
        data = items->data;
        if (data >= 7 || strcmp(item_name(data), tab[1]) != 0) continue;
        del_il(&player->inventory, data);
        push_il(&player->square->items, data);
        free_arr(tab);
        to_send(serv->graphical, PDR, player->id, data);
        return to_send(player, STR_OK);
    }
    free_arr(tab);
    to_send(player, STR_KO);
}
