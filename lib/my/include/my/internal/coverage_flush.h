/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Declare internal utilities for doing flushing of coverage data (for testing 
** functions like abort)
*/

#pragma once


#ifdef LIBMY_COVERAGE
void __gcov_flush(void);
    #define MY_COVERAGE_FLUSH() __gcov_flush()
#else
    #define MY_COVERAGE_FLUSH()
#endif
