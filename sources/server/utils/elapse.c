/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** elapse
*/

#include "server.h"

bool elapse(server_t *serv, clock_t start_time, double unit)
{
    clock_t elapsed_clocks = clock() - start_time;
    double elapsed_time = (double) elapsed_clocks / CLOCKS_PER_SEC;
    double elapsed_units = elapsed_time * serv->freq;

    return elapsed_units >= unit;
}
