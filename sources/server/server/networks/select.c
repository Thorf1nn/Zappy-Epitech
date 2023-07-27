/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** select
*/

#include "server.h"

void fill_select(server_t *serv)
{
    fd_set *read_fds = &(serv->net->read_fds);
    fd_set *write_fds = &(serv->net->write_fds);

    FD_ZERO(read_fds);
    FD_ZERO(write_fds);
    FD_SET(serv->net->fd_server, read_fds);
    for (pl_t *tmp = serv->players; tmp && tmp->data; tmp = tmp->next) {
        FD_SET(tmp->data->fd, read_fds);
        if (len_msg(tmp->data->to_send) > 0) FD_SET(tmp->data->fd, write_fds);
    }
}

bool fd_select(server_t *serv)
{
    network_t *net = serv->net;
    int fd = max_fd(serv) + 1;
    fd_set *read_fds = &(net->read_fds);
    fd_set *write_fds = &(net->write_fds);

    if (select(fd, read_fds, write_fds, NULL, &(net->timeout)) == -1)
        return print_err(false, "select -> %s\n", strerror(errno));
    return true;
}
