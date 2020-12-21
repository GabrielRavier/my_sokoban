/*
** EPITECH PROJECT, 2020
** libmy
** File description:
** Tests assert
*/

#include "tests_header.h"
#include "my/assert.h"
#include "my/string.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

static void handler(int signum)
{
    (void)signum;
}

Test(MY_ASSERT, freebsd_false)
{
    pid_t pid = fork();
    cr_assert(pid >= 0);

    if (pid == 0) {
        struct sigaction action;
        my_memset(&action, 0, sizeof(action));
        action.sa_flags = 0;
        action.sa_handler = &handler;

        sigemptyset(&action.sa_mask);
        sigaction(SIGILL, &action, NULL);
        MY_ASSERT(1 == 1);

        _exit(EXIT_SUCCESS);
    }

    int sta;
    wait(&sta);
    if (WIFSIGNALED(sta) != 0 || WIFEXITED(sta) == 0)
        cr_assert(false && "MY_ASSERT should not have fired");
}

Test(MY_ASSERT, freebsd_true)
{
    pid_t pid = fork();
    cr_assert(pid >= 0);

    if (pid == 0) {
        MY_ASSERT(1 == 2);
        _exit(EXIT_SUCCESS);
    }

    int sta;
    wait(&sta);
    if (WIFSIGNALED(sta) == 0 || WTERMSIG(sta) != SIGILL)
        cr_assert(false && "MY_ASSERT should have fired");
}
