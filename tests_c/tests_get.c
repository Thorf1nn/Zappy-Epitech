/*
** EPITECH PROJECT, 2023
** Tests Criterion
** File description:
** Tests | Get
*/

#include "lib_test.h"

Test(get_args, all_work, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080",
                    "-x", "20", "-y", "20", "-f", "20"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(1, ret);
}

Test(get_args, classic_launch, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server"};
    char **args = data;
    int ret = 1;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 1, args);
    cr_assert_eq(1, ret);
}

Test(get_args, bad_port, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "feur"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 3, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_x, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "31", "-y", "20"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}
Test(get_args, bad_x2, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "9", "-y", "20"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_y, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "20", "-y", "31"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_y2, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080", "-x", "20", "-y", "9"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_freq, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080",
                    "-x", "20", "-y", "9", "-f", "1"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}

Test(get_args, bad_freq2, .init = redirect_all_std)
{
    server_t *serv;
    char *data[] = {"./zappy_server", "-p", "8080",
                    "-x", "20", "-y", "9", "-f", "10001"};
    char **args = data;
    int ret = 0;

    serv = malloc(sizeof(server_t));

    ret = get_args(serv, 7, args);
    cr_assert_eq(0, ret);
}
