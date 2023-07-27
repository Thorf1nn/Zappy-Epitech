/*
** EPITECH PROJECT, 2023
** BOOTSTRAP_ZAPPY_MAIN_C
** File description:
** main
*/

#include "server.h"

int free_exit(char **tab, int ret)
{
    for (int i = 0; tab[i]; i++) free(tab[i]);
    free(tab);
    return ret;
}

int main(int ac, char **av)
{
    server_t server;
    char **tab = calloc(ac + 1, sizeof(char *));

    for (int i = 0; i < ac; i++) tab[i] = strdup(av[i]);
    if (ac == 2 && tab[1] && !strcmp(tab[1], "-help"))
        return free_exit(tab, print_usage());
    if (!get_args(&server, ac, tab)) return free_exit(tab, EXIT_FAILURE);
    free_exit(tab, 0);
    if (init_server(&server)) return EXIT_FAILURE;
    if (!loop_server(&server)) return EXIT_FAILURE;
    free_exit(tab, EXIT_SUCCESS);
    return EXIT_SUCCESS;
}
