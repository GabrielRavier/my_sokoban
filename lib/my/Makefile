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
SOURCE_FILES := assert_fail

# Stuff related to ctype.h
SOURCE_FILES += isprint isupper islower isdigit isalpha isalnum isspace toupper tolower

# Stuff related to math.h
SOURCE_FILES += fabsf fpclassify

# Stuff related to stdio.h
SOURCE_FILES += putchar dputc dputs puts printf/printf printf/vprintf printf/dprintf printf/vdprintf printf/asprintf printf/vasprintf printf/formatter/append_number_base printf/formatter/char printf/formatter/cstring printf/formatter/signed_integer printf/formatter/unsigned_integer printf/formatter/decimal_float printf/formatter/percent_sign printf/parse_conversion_info

# Stuff related to stdlib.h
SOURCE_FILES += qsort qsort_r realloc_size strtol_base_str strtol_base_str_part2

# Stuff related to string.h
SOURCE_FILES += strlen strcpy strncpy strstr strcmp strncmp strcat strncat strchr strspn strcspn strnlen strdup strndup memcpy memmove memchr memset

# Stuff related to my_bigint
SOURCE_FILES += bigint/new_from_int bigint/strtol_base_str bigint/assign bigint/add bigint/add_unsigned bigint/compare bigint/compare_unsigned bigint/sub bigint/sub_unsigned bigint/mul bigint/div bigint/mod bigint/div_mod bigint/neg bigint/to_int bigint/to_string_base bigint/free

# Stuff related to my_checked_multiply
SOURCE_FILES += checked_multiply_int checked_multiply_unsigned

# Stuff related to my_string
SOURCE_FILES += my_string/new_from_string my_string/new my_string/assign my_string/guarantee_can_expand my_string/append my_string/insert my_string/erase my_string/resize my_string/free

# Miscellaneous stuff
SOURCE_FILES += putnbr putnbr_base putnbr_base_width nbr_to_string nbr_to_string_base nbr_to_string_base_width compute_power_rec compute_square_root is_prime find_prime_sup revstr strupcase strlowcase strcapitalize str_isalpha str_isnum str_islower str_isupper str_isprintable count_byte_occurences str_to_word_array show_word_array

TESTS_SOURCE_FILES := strtol_base_str bigint/add bigint/sub bigint/mul bigint/div bigint/mod bigint/strtol_base_str bigint/to_string_base printf/printf

OBJECT_FILES := $(addprefix obj/src/, $(addsuffix .o, $(SOURCE_FILES)))
TESTS_OBJECT_FILES := $(addprefix obj/tests/, $(addsuffix .o, $(TESTS_SOURCE_FILES)))

# r is for inserting with replacement
# c is for creating the archive without a warning when it doesn't exist
# s is for writing an index into the archive
../libmy.a: $(OBJECT_FILES)
	$(AR) rcs $@ $^

tests_binary: $(TESTS_OBJECT_FILES) ../libmy.a
	rm -rf obj/src
	$(MAKE) ../libmy.a CFLAGS="$(CFLAGS) --coverage"
	$(CC) -o $@ $(CFLAGS) -L.. $(TESTS_OBJECT_FILES) -lcriterion -lmy --coverage

../../include/%.h: include/%.h
	@mkdir --parents ../../include/my/internal
	cp $< $@

obj/%.o: %.c
	@mkdir --parents obj/src/bigint
	@mkdir --parents obj/src/my_string
	@mkdir --parents obj/src/printf/formatter
	$(CC) -c $< -o $@ $(CFLAGS)

obj/tests/%.o: ../../tests/libmy/%.c
	@mkdir --parents obj/tests/bigint
	@mkdir --parents obj/tests/printf
	$(CC) -c $< -o $@ $(CFLAGS) --coverage

# Include dependencies
include $(shell [ -d obj ] && find obj/ -type f -name '*.d')

# Remove all object files
clean:
	rm --recursive --force obj

# Remove all object, binary and other produced files
fclean: clean
	rm --recursive --force ../libmy.a tests_binary $(HEADER_FILES)
