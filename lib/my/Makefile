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

# We sometimes need GNU stuff (i.e. asprintf)
override CFLAGS += -D_GNU_SOURCE

.PHONY: all clean fclean

.PREVIOUS: obj/%.o

HEADER_FILES := my my/assert my/bigint my/checked_multiply my/config my/ctype my/macros my/math my/misc my/my_string my/stdio my/stdlib my/string my/strings
HEADER_FILES := $(addprefix ../../include/, $(addsuffix .h, $(HEADER_FILES)))

all: ../libmy.a $(HEADER_FILES)

# The sources for libmy
# Stuff related to assert.h
SOURCE_FILES := assert/assert_fail

# Stuff related to ctype.h
SOURCE_FILES += ctype/isprint ctype/isupper ctype/islower ctype/isdigit ctype/isalpha ctype/isalnum ctype/isspace ctype/toupper ctype/tolower

# Stuff related to math.h
SOURCE_FILES += math/fabsf math/fpclassify

# Stuff related to stdio.h
SOURCE_FILES += stdio/putchar stdio/dputc stdio/dputs stdio/puts stdio/printf/printf stdio/printf/vprintf stdio/printf/dprintf stdio/printf/vdprintf stdio/printf/asprintf stdio/printf/vasprintf stdio/printf/formatter/append_number_base stdio/printf/formatter/utf32_char_to_utf8 stdio/printf/formatter/char stdio/printf/formatter/cstring stdio/printf/formatter/signed_integer stdio/printf/formatter/unsigned_integer stdio/printf/formatter/decimal_float stdio/printf/formatter/percent_sign stdio/printf/formatter/n stdio/printf/formatter/pointer stdio/printf/parse_conversion_info/parse_conversion_info stdio/printf/parse_conversion_info/parse_int stdio/printf/handle_invalid stdio/printf/padding

# Stuff related to stdlib.h
SOURCE_FILES += stdlib/qsort stdlib/qsort_r stdlib/realloc_size stdlib/strtol_base_str stdlib/strtol_base_str_part2

# Stuff related to string.h
SOURCE_FILES += string/strlen string/strcpy string/strncpy string/strstr string/strcmp string/strncmp string/strcat string/strncat string/strchr string/strspn string/strcspn string/strnlen string/strdup string/strndup string/memchr string/memset
ifeq ($(shell uname -p), x86_64)
	SOURCE_FILES += string/memcpy_x86_64 string/memmove_x86_64
else
	SOURCE_FILES += string/memcpy string/memmove
endif

# Stuff related to strings.h
SOURCE_FILES += strings/strcasecmp

# Stuff related to my_bigint
SOURCE_FILES += bigint/new_from_int bigint/strtol_base_str bigint/assign bigint/add bigint/add_unsigned bigint/compare bigint/compare_unsigned bigint/sub bigint/sub_unsigned bigint/mul bigint/div bigint/mod bigint/div_mod bigint/neg bigint/to_int bigint/to_string_base bigint/free

# Stuff related to my_checked_multiply
SOURCE_FILES += checked_multiply/int checked_multiply/unsigned

# Stuff related to my_string
SOURCE_FILES += my_string/new_from_string my_string/new my_string/assign my_string/guarantee_can_expand my_string/append my_string/append_vprintf my_string/insert my_string/erase my_string/resize my_string/free

# Miscellaneous stuff
SOURCE_FILES += misc/compute_power_rec misc/compute_square_root misc/is_prime misc/find_prime_sup misc/revstr misc/strupcase misc/strlowcase misc/strcapitalize misc/str_isalpha misc/str_isnum misc/str_islower misc/str_isupper misc/str_isprintable misc/count_byte_occurences misc/str_to_word_array misc/show_word_array

TESTS_SOURCE_FILES := stdlib/strtol_base_str bigint/add bigint/sub bigint/mul bigint/div bigint/mod bigint/strtol_base_str bigint/to_string_base stdio/printf/printf

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

obj/%.o: %.s
	@mkdir --parents obj/src/string
	$(CC) -c $< -o $@ $(CFLAGS)

obj/%.o: %.c
	@mkdir --parents obj/src/assert
	@mkdir --parents obj/src/bigint
	@mkdir --parents obj/src/checked_multiply
	@mkdir --parents obj/src/ctype
	@mkdir --parents obj/src/math
	@mkdir --parents obj/src/misc
	@mkdir --parents obj/src/my_string
	@mkdir --parents obj/src/stdio/printf/formatter
	@mkdir --parents obj/src/stdio/printf/parse_conversion_info
	@mkdir --parents obj/src/stdlib
	@mkdir --parents obj/src/string
	@mkdir --parents obj/src/strings
	$(CC) -c $< -o $@ $(CFLAGS)

obj/tests/%.o: ../../tests/libmy/%.c
	@mkdir --parents obj/tests/bigint
	@mkdir --parents obj/tests/stdio/printf
	@mkdir --parents obj/tests/stdlib
	$(CC) -c $< -o $@ $(CFLAGS) --coverage

# Include dependencies
include $(shell [ -d obj ] && find obj/ -type f -name '*.d')

# Remove all object files
clean:
	rm --recursive --force obj

# Remove all object, binary and other produced files
fclean: clean
	rm --recursive --force ../libmy.a tests_binary $(HEADER_FILES)
