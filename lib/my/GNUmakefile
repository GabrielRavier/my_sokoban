##
## EPITECH PROJECT, 2020
## libmy
## File description:
## Makefile for libmy.a
##

# We use `override` to enable setting part of CFLAGS on the command line
# This makes the compiler generate dependency files, which will solve any header-related dependency problems we could have had
override CFLAGS += -MMD -MP -MF $@.d

# We need to be able to include the libmy include files
override CFLAGS += -Iinclude

.PHONY: all clean

.PREVIOUS: obj/%.o

all: ../libmy.a ../../include/my.h

# The functions we need to build for the day
SOURCE_FILES := my_putchar my_isneg my_putnbr my_putnbr_base my_putnbr_base_width my_nbr_to_string my_nbr_to_string_base my_nbr_to_string_base_width my_swap my_putstr my_dputs my_puts my_strlen my_getnbr my_getnbr_base my_getnbr_base_part2 my_sort_int_array my_compute_power_rec my_compute_square_root my_is_prime my_find_prime_sup my_strcpy my_strncpy my_revstr my_strstr my_strcmp my_strncmp my_strupcase my_strlowcase my_strcapitalize my_str_isalpha my_str_isnum my_str_islower my_str_isupper my_str_isprintable my_showstr my_showmem my_strcat my_strncat my_isprint my_isupper my_islower my_isdigit my_isalpha my_isalnum my_toupper my_tolower my_strchr my_strspn my_strcspn my_strnlen my_strdup my_strndup my_count_byte_occurences my_checked_multiply my_qsort my_qsort_r my_memcpy my_memchr my_memset my_realloc_size my_str_to_word_array my_show_word_array my_fabsf

OBJECT_FILES := $(addprefix obj/, $(addsuffix .o, $(SOURCE_FILES)))

../libmy.a: libmy.a
	cp $< $@

# r is for inserting with replacement
# c is for creating the archive without a warning when it doesn't exist
# s is for writing an index into the archive
libmy.a: $(OBJECT_FILES)
	$(AR) rcs $@ $^

../../include/my.h: include/my.h
	@mkdir --parents ../../include
	cp $< $@

obj/%.o: src/%.c
	@mkdir --parents obj
	$(CC) -c $< -o $@ $(CFLAGS)

# Include dependencies
include $(wildcard obj/*.d)

# Remove all object files
clean:
	rm --recursive --force obj

# Remove all object, binary and other produced files
fclean:
	rm --recursive --force obj ../libmy.a ../../include/my.h
