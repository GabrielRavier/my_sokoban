/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests memmove
*/

#include "my/string.h"

#define MEMMOVE_LIKE_FUNC(destination, source, n) cr_assert_eq(my_memmove(destination, source, n), destination)
#define MEMMOVE_LIKE_FUNC_TEST_NAME my_memmove

#include "memmove_like.h"
