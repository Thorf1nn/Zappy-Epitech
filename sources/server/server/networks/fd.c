/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** fd
*/

#include "server.h"

int max_fd(server_t *serv)
{
    int fd_max = serv->net->fd_server;

    for (pl_t *tmp = serv->players; tmp; tmp = tmp->next)
        if (tmp->data && tmp->data->fd > fd_max) fd_max = tmp->data->fd;
    serv->net->fd_max = fd_max;
    return fd_max;
}

bool new_fd(server_t *serv)
{
    struct sockaddr_in addr_in;
    struct sockaddr *addr = (struct sockaddr *) &addr_in;
    socklen_t addr_len = sizeof(addr_in);
    int fd = accept(serv->net->fd_server, addr, &addr_len);

    if (fd == -1) return print_err(false, "accept -> %s\n", strerror(errno));
    new_player(serv, fd);
    return true;
}

bool handle_fd(player_t *player)
{
    char buff[READ_SIZE + 1];
    ssize_t size;

    if (player->disconnected) return false;
    memset(buff, 0, READ_SIZE + 1);
    if ((size = read(player->fd, buff, READ_SIZE)) <= 0)
        player->disconnected = true;
    else if (size > 0 && strlen(buff) > 0) {
        player->s_buff = strlen(player->buff) + strlen(buff) + 1;
        player->buff = realloc(player->buff, player->s_buff);
        strcat(player->buff, buff);
    }
    for (int i = 0; player->buff[i]; i++)
        if (player->buff[i] == '\n') player->nb_cmd++;
    return true;
}
