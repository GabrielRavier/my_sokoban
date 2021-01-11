/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines part 2 of strtol_base_str
*/

#include "my/internal/strtol_base_str_part2.h"
#include "my/string.h"

// Checks whether there is a valid digit at *digit_ptr and gets it into
// digit_ptr, with the base being the contents of base. The return value
// determines whether this function was successful at finding a digit
bool my_find_digit_from_base(const char *digit_character_ptr, const char *base,
    unsigned char *digit_ptr)
{
    const char character = *digit_character_ptr;
    const char *strchr_result;

    if (character == '\0')
        return (false);
    strchr_result = my_strchr(base, character);
    if (!strchr_result)
        return (false);
    *digit_ptr = (unsigned char)(strchr_result - base);
    return (true);
}
