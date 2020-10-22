/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Splits a string into words
*/

#include "my/misc.h"
#include "my/ctype.h"
#include "my/string.h"
#include "my/stdlib.h"
#include <stdlib.h>

static size_t get_word_length(const char *string)
{
    size_t result = 0;

    while (my_isalnum(string[result]))
        ++result;
    return (result);
}

static size_t get_non_word_length(const char *string)
{
    size_t result = 0;

    while (!my_isalnum(string[result]) && (string[result] != '\0'))
        ++result;
    return (result);
}

// This primitive tokenizer works in the following way :
// 1: Try to find a word
// 2: If there is none, add a NULL and return
// 3: Add the word to the array
// 4: Go back to 1 with the beginning of the next word
char **my_str_to_word_array(const char *string)
{
    size_t result_size = 0;
    char **result = NULL;
    size_t word_length;

    string += get_non_word_length(string);
    while (1) {
        word_length = get_word_length(string);
        result = (char **)my_realloc_size(result,
            (result_size + 1) * sizeof(char *), result_size * sizeof(char *));
        ++result_size;
        if (word_length == 0) {
            result[result_size - 1] = NULL;
            return (result);
        }
        result[result_size - 1] = my_strndup(string, word_length);
        string += (word_length + get_non_word_length(string + word_length));
    }
}
