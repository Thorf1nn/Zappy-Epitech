/*
** EPITECH PROJECT, 2023
** server [WSL: Ubuntu]
** File description:
** strarr
*/

#include "server.h"

void free_arr(char **tab)
{
    for (int i = 0; tab[i]; i++) free(tab[i]);
    free(tab);
}

int count_words(const char *str, const char *del)
{
    int count = 0;
    char *token = strtok(strdup(str), del);

    for (; token != NULL; token = strtok(NULL, del)) count++;
    return count;
}

char **strarr(const char *str, const char *del)
{
    char *strcopy = strdup(str);
    int count = count_words(strcopy, del) + 1;
    char **words = (char **) calloc(count, sizeof(char *));
    char *token = strtok(strcopy, del);

    memset(words, 0, count * sizeof(char *));
    for (int i = 0; token != NULL; i++, token = strtok(NULL, del))
        words[i] = strdup(token);
    free(strcopy);
    return words;
}

bool compare(char *cmd, int nb)
{
    char **tab = strarr(cmd, " ");
    int i;

    for (i = 0; tab[i];) i++;
    free_arr(tab);
    return i != nb ? false : true;
}
