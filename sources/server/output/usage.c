/*
** EPITECH PROJECT, 2023
** B_YEP_400_MPL_4_1_ZAPPY_HUGO_ESCHLIMANN_USAGE_C
** File description:
** usage
*/

#include "server.h"

int print_usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width ");
    printf("-y height -n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\tis the port number\n");
    printf("\twidth\tis the width of the world\n");
    printf("\tweight\tis the height of the world\n");
    printf("\tnameX\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf(
        "\tfreq\tis the reciprocal of time unit for execution of actions\n");
    return EXIT_SUCCESS;
}

void usage_error(void)
{
    fprintf(stderr, "USAGE: ./zappy_server -help\n");
    exit(EXIT_FAILURE);
}

int print_usage_error(char *str pass, int ret)
{
    fprintf(stderr, "%s\nUSAGE: ./zappy_server -help\n", str);
    return ret;
}

int print_err(int ret, char *str pass, ...)
{
    va_list ap;

    va_start(ap, str);
    vfprintf(stderr, str, ap);
    va_end(ap);
    return ret;
}
