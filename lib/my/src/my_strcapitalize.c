/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Capitalizes the first letter of each word
*/

#include "my/misc.h"
#include "my/ctype.h"
#include <stdbool.h>

char *my_strcapitalize(char *str)
{
    bool is_in_word = false;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (my_isalnum(str[i])) {
            str[i] = is_in_word ? my_tolower(str[i]) : my_toupper(str[i]);
            is_in_word = true;
        } else
            is_in_word = false;
    }
    return (str);
}
