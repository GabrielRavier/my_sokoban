/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Tests execvp
*/

#include "../tests_header.h"
#include "my/stdio.h"
#include "my/unistd.h"
#include "my/stdlib.h"
#include "my/string.h"
#include <stdio.h>
#include <unistd.h>
#include <libgen.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

Test(my_execvp, glibc_1)
{
    // Try execvp on a non-existing file
    char *current_working_directory = get_current_dir_name();
    cr_assert_neq(current_working_directory, NULL);

    cr_assert_eq(my_setenv("PATH", current_working_directory, 1), 0);

    char *argv[] = { "does-not-exist-dwpoqjfqw9jf980231jf1", NULL };
    errno = 0;
    cr_assert_eq(my_execvp(argv[0], argv), -1);
    free(current_working_directory);
    cr_assert_eq(errno, ENOENT);
}

Test(my_execvp, glibc_2)
{
    // Create a copy of /bin/sh and make sure we can't execute it and get EACCES if we chmod it to be non-executable
    char dir_template[] = "/tmp/execvp_acces_test.XXXXXX";
    cr_assert_neq(mkdtemp(dir_template), NULL);

    char *command;
    int filename_offset;
    cr_assert_geq(my_asprintf(&command, "cp /bin/sh %n%s/cp_test_copy", &filename_offset, dir_template), 0);
    cr_assert_eq(system(command), 0);

    char *filename = command + filename_offset;
    cr_assert_eq(chmod(filename, 0666), 0);

    cr_assert_eq(my_setenv("PATH", dir_template, 1), 0);

    char *argv[] = { basename(filename), NULL };
    errno = 0;
    cr_assert_eq(my_execvp(filename, argv), -1);
    free(command);
    cr_assert_eq(errno, EACCES);
}

Test(my_execvp, glibc_3)
{
    char dir_template[] = "/tmp/execvp_script_test.XXXXXX";
    cr_assert_neq(mkdtemp(dir_template), NULL);

    // Create a (temporary) file and put `echo foo` in it
    char *filename;
    cr_assert_geq(my_asprintf(&filename, "%s/test_script", dir_template), 0);

    int temp_file = creat(filename, O_WRONLY);
    my_dputs("echo foo\n", temp_file);
    fchmod(temp_file, 0700);
    close(temp_file);

    // Set PATH to only contain the directory with the temporary script in it
    cr_assert_eq(my_setenv("PATH", dir_template, 1), 0);

    int file_descriptors[2];
    cr_assert_eq(pipe(file_descriptors), 0);
    
    pid_t child_pid = fork();
    cr_assert_neq(child_pid, -1);
    if (child_pid == 0) {
        // Make stdout be piped to the parent
        cr_assert_neq(dup2(file_descriptors[1], STDOUT_FILENO), -1);
        close(file_descriptors[1]);

        // (hopefully) get my_execvp to start up /bin/sh /tmp/execvp_test.XXXXXX/test_script
        char *argv[] = { filename, NULL };
        my_execvp(basename(filename), argv);
        cr_assert(false && "execvp failed");
    }

    // We have no need for the filename anymore: I guess we can't solve the "leak" on the child side, though
    free(filename);

    // Close the file descriptor so that last `read` reports correctly that the write end of the pipe was closed instead of blocking
    close(file_descriptors[1]);

    // Read the entire output of the child process and check it is `foo\n`
    char output[4];
    size_t read_bytes = 0;
    ssize_t read_result;
    do {
        read_result = read(file_descriptors[0], output + read_bytes, sizeof(output) - read_bytes);
        cr_assert_gt(read_result, 0);
        read_bytes += read_result;
    } while (read_bytes < sizeof(output));
    cr_assert_eq(read(file_descriptors[0], output, 1), 0);
    cr_assert_eq(my_memcmp(output, "foo\n", 4), 0);
}

Test(my_execvp, glibc_4)
{
    // Note: this *could* fail if someone had `does-not-exist` exist somehow
    struct stat stat_buffer;

    cr_assert_eq(stat("does-not-exist", &stat_buffer), -1);
    cr_assert_eq(stat("/bin/does-not-exist", &stat_buffer), -1);
    cr_assert_eq(stat("/usr/bin/does-not-exist", &stat_buffer), -1);
    my_unsetenv("PATH");

    char *argv[] = { "does-not-exist", NULL };
    cr_assert_eq(my_execvp(argv[0], argv), -1);
    cr_assert_eq(errno, ENOENT);
}

