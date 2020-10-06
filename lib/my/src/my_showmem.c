/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Prints a memory dump
*/

#include "my.h"

static void do_print_printable_16_bytes(
    const char *current_16_bytes, int remaining_size)
{
    for (int i = 0; i < 16; ++i)
        if ((i < remaining_size) && my_isprint(current_16_bytes[i]))
            my_putchar(current_16_bytes[i]);
        else
            my_putchar('.');
}

static void do_16_bytes(
    const char *current_16_bytes, int byte_hex_address, int remaining_size)
{
    my_putnbr_base_width(byte_hex_address, "0123456789abcdef", 8);
    my_putchar(':');
    my_putchar(' ');

    for (int i = 0; i < 16; ++i) {
        if (i < remaining_size)
            my_putnbr_base_width(current_16_bytes[i], "0123456789abcdef", 2);
        else {
            my_putchar(' ');
            my_putchar(' ');
        }

        if ((i % 2) == 1)
            my_putchar(' ');
    }

    do_print_printable_16_bytes(current_16_bytes, remaining_size);
    my_putchar('\n');
}

int my_showmem(const char *str, int size)
{
    for (int i = 0; i < size; i += 0x10)
        do_16_bytes(str + i, i, size - i);

    return 0;
}
