/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** cmd_inv
*/

#include "server.h"

void cmd_inv(server_t *serv pass, player_t *player, char *cmd)
{
    int *res;
    char buff[READ_SIZE + 1] = {0};

    if (!compare(cmd, 1)) return to_send(player, STR_KO);
    res = get_resources(player->inventory);
    buff[0] = '[';
    for (int i = 0; i < 7; i++)
        strcats(buff, " ", item_name((item_t) i), " ", itos(res[i]),
            i == 6 ? "" : ",", NULL);
    strcats(buff, " ]\n", NULL);
    to_send(player, buff);
    free(res);
}
