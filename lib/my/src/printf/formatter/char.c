/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements vasprintf_format_char
*/

#include "my/internal/printf/formatter.h"
#include <wchar.h>
#include <sys/types.h>

// We assume wide characters are UTF-32 and that the multibyte representation is
// UTF-8 because I am *not* going to implement this shit for every single
// encoding out there
static size_t do_lead_and_length(wchar_t wide_char, unsigned char *lead)
{
    if ((wide_char & ~0x7F) == 0) {
        *lead = 0;
        return 1;
    }
    if ((wide_char & ~0x7FF) == 0) {
        *lead = 0xC0;
        return 2;
    }
    if ((wide_char & ~0xFFFF) == 0) {
        *lead = 0xE0;
        return 3;
    }
    if ((wide_char & ~0x1FFFFF) == 0) {
        *lead = 0xF0;
        return 4;
    }
    return 0;
}

static size_t utf32_char_to_utf8(char *destination, wchar_t wide_char)
{
    size_t length;
    unsigned char lead;

    if (wide_char == L'\0') {
        *destination = '\0';
        return 1;
    }
    length = do_lead_and_length(wide_char, &lead);
    if (length == 0)
        return 0;
    for (size_t i = length - 1; i > 0; --i) {
        destination[i] = (wide_char & 0x3F) | 0x80;
        wide_char >>= 6;
    }
    *destination = (wide_char & 0xFF) | lead;
    return length;
}

struct my_string *asprintf_format_char(struct my_string *destination,
    va_list arguments, struct my_printf_conversion_info *format_info)
{
    char buffer[4];

    if (format_info->length_modifier != PRINTF_LENGTH_MODIFIER_LONG)
        my_string_append_char(destination, va_arg(arguments, int));
    else
        my_string_append(destination, buffer, utf32_char_to_utf8(buffer,
            va_arg(arguments, wint_t)));
    return (NULL);
}
