/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements asprintf_utf32_char_to_utf8
*/

#include "my/internal/printf/formatter.h"

// We assume wide characters are UTF-32 and that the multibyte representation is
// UTF-8 because I am *not* going to implement this shit for every single
// encoding out there
static size_t do_lead_and_length(wchar_t wide_char, unsigned char *lead)
{
    if ((wide_char & ~0x7F) == 0) {
        *lead = 0;
        return (1);
    }
    if ((wide_char & ~0x7FF) == 0) {
        *lead = 0xC0;
        return (2);
    }
    if ((wide_char & ~0xFFFF) == 0) {
        *lead = 0xE0;
        return (3);
    }
    if ((wide_char & ~0x1FFFFF) == 0) {
        *lead = 0xF0;
        return (4);
    }
    return (0);
}

size_t asprintf_utf32_char_to_utf8(char *destination, wchar_t wide_char)
{
    size_t length;
    unsigned char lead;

    if (wide_char == L'\0') {
        *destination = '\0';
        return (1);
    }
    length = do_lead_and_length(wide_char, &lead);
    if (length == 0)
        return (0);
    for (size_t i = length - 1; i > 0; --i) {
        destination[i] = (wide_char & 0x3F) | 0x80;
        wide_char >>= 6;
    }
    *destination = (wide_char & 0xFF) | lead;
    return (length);
}
