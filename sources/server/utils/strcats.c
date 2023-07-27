/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** strcats
*/

#include "server.h"

void strcats(char *result, ...)
{
    va_list args;
    va_start(args, result);

    char *str = va_arg(args, char *);
    while (str != NULL) {
        strcat(result, str);
        str = va_arg(args, char *);
    }

    va_end(args);
}
