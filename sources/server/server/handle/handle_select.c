/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** handle_select
*/

#include "server.h"

bool handle_select(server_t *serv)
{
    fd_set *read_fds = &(serv->net->read_fds);
    fd_set *write_fds = &(serv->net->write_fds);

    if (FD_ISSET(serv->net->fd_server, read_fds)) new_fd(serv);
    for (pl_t *tmp = serv->players; tmp && tmp->data; tmp = tmp->next) {
        if (FD_ISSET(tmp->data->fd, read_fds)) handle_fd(tmp->data);
        if (FD_ISSET(tmp->data->fd, write_fds)) send_to(tmp->data);
    }
    return true;
}
