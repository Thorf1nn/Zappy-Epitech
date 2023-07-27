/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** server
*/
#include "server.h"

int create_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;

    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &reuse,
            sizeof(reuse))
        < 0) {
        perror("setsockopt");
        exit(EXIT_FAILED);
    }
    return sockfd;
}

int create_server(int port)
{
    int fd = create_socket();
    struct sockaddr_in sock_in = {0};

    if (fd == -1) return -1;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(port);
    sock_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(fd, (struct sockaddr *) &sock_in, sizeof(sock_in)) < 0) {
        perror("bind");
        close(fd);
        exit(EXIT_FAILED);
    }
    if (listen(fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(fd);
        exit(EXIT_FAILED);
    }
    return fd;
}

int init_server(server_t *serv)
{
    int fd = create_server(serv->port);
    build_board(serv);
    create_eggs(serv);
    serv->net = calloc(1, sizeof(network_t));
    serv->net->fd_server = fd;
    serv->net->timeout.tv_sec = 0;
    serv->net->timeout.tv_usec = 1 / serv->freq;
    return 0;
}
