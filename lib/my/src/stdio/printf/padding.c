/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Handles padding for vasprintf
*/

#include "my/internal/printf/padding.h"
#include "my/internal/printf/formatter.h"

static void do_padding_loop(struct my_string *destination,
    size_t destination_length_before_conversion, size_t converted_length,
    struct my_printf_conversion_info *conversion_info)
{
    while (converted_length++ < (size_t)conversion_info->field_width)
        if (conversion_info->flag_minus)
            my_string_append_char(destination, ' ');
        else
            my_string_insert_char(destination,
                conversion_info->flag_0 ? '0' : ' ',
                destination_length_before_conversion);
}

void asprintf_do_padding(const struct asprintf_do_padding_params *params)
{
    const size_t converted_length = params->destination->length -
        params->destination_length_before_conversion +
        (params->prefixed_string ? params->prefixed_string->length : 0);

    if (params->formatting_func != &asprintf_format_unsigned_integer &&
        params->formatting_func != &asprintf_format_signed_integer &&
        params->formatting_func != &asprintf_format_pointer)
        params->conversion_info->flag_0 = false;
    if (!params->conversion_info->flag_0 && params->prefixed_string)
        my_string_insert(params->destination, params->prefixed_string->string,
            params->prefixed_string->length,
            params->destination_length_before_conversion);
    do_padding_loop(params->destination,
        params->destination_length_before_conversion, converted_length,
        params->conversion_info);
    if (params->conversion_info->flag_0 && params->prefixed_string)
        my_string_insert(params->destination, params->prefixed_string->string,
            params->prefixed_string->length,
            params->destination_length_before_conversion);
    my_string_free(params->prefixed_string);
}
