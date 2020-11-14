/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements n conversion specifier
*/

#include "my/internal/printf/formatter.h"
#include <sys/types.h>
#include <stdint.h>

static struct my_string *do_other(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info)
{
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_INTMAX) {
        *va_arg(*arguments, intmax_t *) = destination->length;
        return NULL;
    }
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_SIZE_T) {
        *va_arg(*arguments, ssize_t *) = destination->length;
        return NULL;
    }
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_PTRDIFF_T) {
        *va_arg(*arguments, ptrdiff_t *) = destination->length;
        return NULL;
    }
    *va_arg(*arguments, int *) = destination->length;
    return NULL;
}

struct my_string *asprintf_format_n(struct my_string *destination,
    va_list *arguments, struct my_printf_conversion_info *format_info)
{
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_CHAR) {
        *va_arg(*arguments, signed char *) = destination->length;
        return NULL;
    }
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_SHORT) {
        *va_arg(*arguments, short *) = destination->length;
        return NULL;
    }
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG) {
        *va_arg(*arguments, long *) = destination->length;
        return NULL;
    }
    if (format_info->length_modifier == PRINTF_LENGTH_MODIFIER_LONG_LONG) {
        *va_arg(*arguments, long long *) = destination->length;
        return NULL;
    }
    return do_other(destination, arguments, format_info);
}
