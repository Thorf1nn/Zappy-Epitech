/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** itos
*/

#include "server.h"

char *itos(int nb)
{
    static char buff[100] = {0};

    sprintf(buff, "%d", nb);
    return buff;
}
