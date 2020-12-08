/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Implements my_memcmp
*/

#include "my/string.h"
#include "my/strings.h"

int my_memcmp(const void *s1, const void *s2, size_t length)
{
    const char *char_s1 = s1;
    const char *char_s2 = s2;

    for (size_t i = 0; i < length; ++i)
        if (char_s1[i] != char_s2[i])
            return (char_s1[i] - char_s2[i]);
    return (0);
}

// Declare bcmp as an alias for memcmp, since a valid memcmp will also be a
// valid bcmp (though the inverse is not true). We do this here, as this
// would error if we didn't do it in the same TU as the one where memcmp is
// defined
int my_bcmp(const void *, const void *, size_t)
    MY_ATTRIBUTE((alias("my_memcmp")));
