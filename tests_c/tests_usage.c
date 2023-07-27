/*
** EPITECH PROJECT, 2023
** Tests Criterion
** File description:
** Tests | Usage
*/

#include "lib_test.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(print_usage, check_message, .init = redirect_all_std)
{
    print_usage();

    cr_assert_eq(0, 0);
}

Test(print_usage_error, usage_error2, .init = redirect_all_std)
{
    int ret = print_usage_error("Feur", 84);

    cr_assert_eq(ret, 84);
}
