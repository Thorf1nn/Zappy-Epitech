/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_take
*/

#include "server.h"

void cmd_take(server_t *serv, player_t *player, char *cmd)
{
    char **tab = strarr(cmd, " ");
    item_t data;

    if (!compare(cmd, 2)) return to_send(player, STR_KO);
    for (il_t *items = player->square->items; items; items = items->next) {
        data = items->data;
        if (data >= 7 || strcmp(item_name(data), tab[1]) != 0) continue;
        del_il(&player->square->items, data);
        push_il(&player->inventory, data);
        free_arr(tab);
        to_send(serv->graphical, PGT, player->id, data);
        return to_send(player, STR_OK);
    }
    free_arr(tab);
    to_send(player, STR_KO);
}
