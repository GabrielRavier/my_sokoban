/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Defines strcat
*/

#include "my/string.h"

char *my_strcat(char *destination, const char *source)
{
    my_strcpy(destination + my_strlen(destination), source);
    return (destination);
}
