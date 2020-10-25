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

.PHONY: all clean fclean

.PREVIOUS: obj/%.o

HEADER_FILES := my my/bigint my/checked_multiply my/config my/ctype my/macros my/math my/misc my/stdio my/stdlib my/string my/my_string
HEADER_FILES := $(addprefix ../../include/, $(addsuffix .h, $(HEADER_FILES)))

all: ../libmy.a $(HEADER_FILES)

# The sources for libmy
# Stuff related to assert.h
SOURCE_FILES := my_assert_fail

# Stuff related to ctype.h
SOURCE_FILES += my_isprint my_isupper my_islower my_isdigit my_isalpha my_isalnum my_isspace my_toupper my_tolower

# Stuff related to math.h
SOURCE_FILES += my_fabsf

# Stuff related to stdio.h
SOURCE_FILES += my_putchar my_dputc my_dputs my_puts

# Stuff related to stdlib.h
SOURCE_FILES += my_qsort my_qsort_r my_realloc_size my_strtol_base_str my_strtol_base_str_part2

# Stuff related to string.h
SOURCE_FILES += my_strlen my_strcpy my_strncpy my_strstr my_strcmp my_strncmp my_strcat my_strncat my_strchr my_strspn my_strcspn my_strnlen my_strdup my_strndup my_memcpy my_memmove my_memchr my_memset

# Stuff related to my_bigint
SOURCE_FILES += bigint/set_str bigint/add bigint/add_unsigned bigint/compare_unsigned bigint/sub_unsigned bigint/dprint bigint/free bigint/at_least_digits

# Stuff related to my_checked_multiply
SOURCE_FILES += my_checked_multiply_int my_checked_multiply_unsigned

# Stuff related to my_string
SOURCE_FILES += my_string/new_from_string my_string/new my_string/guarantee_can_expand my_string/append my_string/insert my_string/erase my_string/free

# Miscellaneous stuff
SOURCE_FILES += my_putnbr my_putnbr_base my_putnbr_base_width my_nbr_to_string my_nbr_to_string_base my_nbr_to_string_base_width my_compute_power_rec my_compute_square_root my_is_prime my_find_prime_sup my_revstr my_strupcase my_strlowcase my_strcapitalize my_str_isalpha my_str_isnum my_str_islower my_str_isupper my_str_isprintable my_count_byte_occurences my_str_to_word_array my_show_word_array

TESTS_SOURCE_FILES := my_strtol_base_str

OBJECT_FILES := $(addprefix obj/src/, $(addsuffix .o, $(SOURCE_FILES)))
TESTS_OBJECT_FILES := $(addprefix obj/tests/, $(addsuffix .o, $(TESTS_SOURCE_FILES)))

# r is for inserting with replacement
# c is for creating the archive without a warning when it doesn't exist
# s is for writing an index into the archive
../libmy.a: $(OBJECT_FILES)
	$(AR) rcs $@ $^

tests_binary: ../libmy.a $(TESTS_OBJECT_FILES)
	$(CC) -o $@ -L.. $(TESTS_OBJECT_FILES) -lcriterion -lmy

../../include/%.h: include/%.h
	@mkdir --parents ../../include/my/internal
	cp $< $@

obj/%.o: %.c
	@mkdir --parents obj/src/bigint
	@mkdir --parents obj/src/my_string
	@mkdir --parents obj/tests
	$(CC) -c $< -o $@ $(CFLAGS)

# Include dependencies
include $(wildcard obj/*.d)

# Remove all object files
clean:
	rm --recursive --force obj

# Remove all object, binary and other produced files
fclean: clean
	rm --recursive --force ../libmy.a $(HEADER_FILES)
