/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** params
*/

#include "server.h"

static const server_t TMP_SERVER = {-1, -1, -1, -1, -1, -1, -1, NULL, NULL,
    NULL, NULL, NULL, 0, NULL};

static const check_args_t CHECK_ARGS[] = {
    {"-p", (check) int_check, "Port must be a positive number",
        (int) ((char *) &TMP_SERVER.port - (char *) &TMP_SERVER)},
    {"-x", (check) int_check, "Width must be a positive number",
        (int) ((char *) &TMP_SERVER.width - (char *) &TMP_SERVER)},
    {"-y", (check) int_check, "Height must be a positive number",
        (int) ((char *) &TMP_SERVER.height - (char *) &TMP_SERVER)},
    {"-c", (check) int_check, "ClientsNb must be a positive number",
        (int) ((char *) &TMP_SERVER.clients_nb - (char *) &TMP_SERVER)},
    {"-f", (check) int_check, "Freq must be a positive number",
        (int) ((char *) &TMP_SERVER.freq - (char *) &TMP_SERVER)},
    {"-n", (check) add_param_team, "Team name must be a string",
        (int) ((char *) &TMP_SERVER.teams - (char *) &TMP_SERVER)},
    {NULL, NULL, NULL, 0}};

bool int_check(int *data, char **av)
{
    if (!av[0]) return false;
    *data = atoi(av[0]);
    if (*data <= 0) return false;
    return true;
}

bool add_param_team(team_t ***param, char **av)
{
    int i;

    for (i = 0; av && av[i] && av[i][0] != '-'; i++) i++;
    if (!i) return false;
    *param = calloc(1, sizeof(team_t *) * (i + 1));
    for (i = 0; av[i] && av[i][0] != '-'; i++) {
        (*param)[i] = calloc(1, sizeof(team_t));
        (*param)[i]->name = strdup(av[i]);
    }
    (*param)[i] = NULL;
    return true;
}

bool check_args(server_t *serv, int i, char **av)
{
    for (int j = 0; CHECK_ARGS[j].flag; j++) {
        if (strcmp(CHECK_ARGS[j].flag, av[i])) continue;
        if (!CHECK_ARGS[j].check(
                (void *) ((char *) serv + CHECK_ARGS[j].offset), av + i + 1))
            return print_usage_error(CHECK_ARGS[j].error, false);
    }
    return true;
}
