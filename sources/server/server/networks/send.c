/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** send
*/

#include "server.h"

void to_send(player_t *player, char *cmd, ...)
{
    va_list ap;
    char *buff;

    if (!player) return;
    buff = calloc(READ_SIZE + 1, sizeof(char));
    va_start(ap, cmd);
    vsprintf(buff, cmd, ap);
    va_end(ap);
    push_msg(&(player->to_send), buff);
}

bool send_to(player_t *player)
{
    if (!player->to_send) return true;
    for (ml_t *msg = player->to_send; msg; msg = msg->next)
        if (write(player->fd, msg->data, strlen(msg->data)) == -1)
            return !(player->disconnected = true);
    clear_msg(&(player->to_send));
    return true;
}
