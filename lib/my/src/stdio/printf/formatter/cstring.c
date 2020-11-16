/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements vasprintf_format_cstring
*/

#include "my/internal/printf/formatter.h"
#include "my/string.h"
#include "my/ctype.h"

static void do_wchar_string(struct my_string *destination,
    struct my_printf_conversion_info *format_info, const wchar_t *wide_string)
{
    size_t bytes_written = 0;
    size_t wide_character_length;
    char buffer[4];

    if (!wide_string)
        wide_string = (size_t)format_info->precision >= 6 ? L"(null)" : L"";
    while (*wide_string != L'\0') {
        wide_character_length =
            asprintf_utf32_char_to_utf8(buffer, *wide_string++);
        if ((bytes_written + wide_character_length) >
            (size_t)format_info->precision)
            break;
        my_string_append(destination, buffer, wide_character_length);
        bytes_written += wide_character_length;
    }
}

static void do_string_loop(struct my_string *destination,
    const char *string_argument,
    struct my_printf_conversion_info *format_info)
{
    for (size_t i = 0; string_argument[i] != '\0' &&
            i < (size_t)format_info->precision; ++i)
        if ((format_info->conversion_specifier == 's') ||
            (my_isprint(string_argument[i])))
            my_string_append_char(destination, string_argument[i]);
        else {
            my_string_append_char(destination, '\\');
            my_string_append_char(destination, "01234567"
                [(unsigned char)string_argument[i] / 0100]);
            my_string_append_char(destination, "01234567"
                [(unsigned char)string_argument[i] / 010 % 010]);
            my_string_append_char(destination, "01234567"
                [(unsigned char)string_argument[i] % 010]);
        }
}

// We treat LONG_LONG as if it was LONG for glibc compatibility
// I would support the SUS S specifier, but the epitech mandates that we use it
// for a different purpose
struct my_string *asprintf_format_cstring(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info)
{
    const char *string_argument;

    if (format_info->length_modifier != PRINTF_LENGTH_MODIFIER_LONG &&
        format_info->length_modifier != PRINTF_LENGTH_MODIFIER_LONG_LONG) {
        string_argument = va_arg(*arguments, const char *);
        if (!string_argument)
            string_argument = (size_t)format_info->precision >= 6
                ? "(null)" : "";
        do_string_loop(destination, string_argument, format_info);
    } else
        do_wchar_string(destination, format_info,
            va_arg(*arguments, const wchar_t *));
    return (NULL);
}
