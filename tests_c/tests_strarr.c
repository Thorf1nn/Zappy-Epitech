/*
** EPITECH PROJECT, 2023
** Tests Criterion
** File description:
** Tests | Strarr
*/

#include "lib_test.h"

Test(count_words, remove_str)
{
    const char *str = "Il a dit quoi j'ai dit feur";
    int new = count_words(str, " ");

    cr_assert_eq(7, new);
}

Test(strarr, separe_words)
{
    int i = 0;
    char *str = "Luca il n'a pas les cramptés";
    char **words = strarr(str, " ");

    while (words[i] != NULL) {
        i += 1;
    }
    cr_assert_eq(6, i);
    cr_assert_str_eq(words[0], "Luca");
    cr_assert_str_eq(words[1], "il");
    cr_assert_str_eq(words[2], "n'a");
    cr_assert_str_eq(words[3], "pas");
    cr_assert_str_eq(words[4], "les");
    cr_assert_str_eq(words[5], "cramptés");
}

Test(compare, compare_good_nb_words)
{
    int i = 0;
    char *str = "Luca il n'a pas les cramptés";
    bool comp = compare(str, 6);

    cr_assert_eq(comp, 1);
}

Test(compare, compare_bad_nb_words)
{
    int i = 0;
    char *str = "Luca il n'a pas les cramptés";
    bool comp = compare(str, 5);

    cr_assert_eq(comp, 0);
}
