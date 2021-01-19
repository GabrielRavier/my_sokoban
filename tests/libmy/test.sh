#!/usr/bin/env bash

# Execute tests from the directory that which contains the script
cd "$(dirname "$0")"

TESTS_BINARY=../../lib/my/tests_binary

do_test_process()
{
    $TESTS_BINARY --filter="$1*"
    echo "$1 done"
}

# Do all the tests that aren't printf
for i in $($TESTS_BINARY --list | grep -vE '^([├└]|my_printf)' | cut -d: -f1)
do
    do_test_process "$i"&
done

# Do printf tests without the actual printf being checked (in case ASAN in running, it might fuck up tests related to invalidity, considering it doesn't like some of the behaviour we test (that glibc accepts, but is invalid)
ASAN_OPTIONS=check_printf=0 do_test_process my_printf&

# Wait for all tests to be over before exiting
wait
