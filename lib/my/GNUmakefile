##
## EPITECH PROJECT, 2020
## Unix and C Lab Seminar - Day 07
## File description:
## Makefile for libmy.a
##

# We use `override` to enable setting part of CFLAGS on the command line
# This makes the compiler generate dependency files, which will solve any header-related dependency problems we could have had
override CFLAGS += -MMD -MP -MF $@.d

# We need to be able to include the libmy include files
override CFLAGS += -I../../include/

.PHONY: all clean

.PREVIOUS: obj/%.o

all: libmy.a

# The functions we need to build for the day
SOURCE_FILES := my_putchar my_isneg my_put_nbr my_putnbr_base my_putnbr_base_width my_swap my_putstr my_strlen my_getnbr my_sort_int_array my_compute_power_rec my_compute_square_root my_is_prime my_find_prime_sup my_strcpy my_strncpy my_revstr my_strstr my_strcmp my_strncmp my_strupcase my_strlowcase my_strcapitalize my_str_isalpha my_str_isnum my_str_islower my_str_isupper my_str_isprintable my_showstr my_showmem my_strcat my_strncat

OBJECT_FILES := $(addprefix obj/, $(addsuffix .o, $(SOURCE_FILES)))

# r is for inserting with replacement
# c is for creating the archive without a warning when it doesn't exist
# s is for writing an index into the archive
# v is for verbosity (probably remove this at some point)
libmy.a: $(OBJECT_FILES)
	$(AR) rvcs $@ $^

obj/%.o: src/%.c
	@mkdir --parents obj
	$(CC) -c $< -o $@ $(CFLAGS)

# Include dependencies
include $(wildcard obj/*.d)

# Remove all object and binary files
clean:
	rm --recursive --force obj libmy.a
