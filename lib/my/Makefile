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

# Check for feature flags
ifndef USE_LIBC_FILE
$(error You must define USE_LIBC_FILE)
endif
ifndef HAS_LIBC_ALLOC
$(error You must define HAS_LIBC_ALLOC)
endif
ifndef HAS_LIBC_READ
$(error You must define HAS_LIBC_READ)
endif
ifndef HAS_LIBC_WRITE
$(error You must define HAS_LIBC_WRITE)
endif
ifndef HAS_LIBC_EXECVE
$(error You must define HAS_LIBC_EXECVE)
endif
ifndef HAS_LIBC_ISATTY
$(error You must define HAS_LIBC_ISATTY)
endif
ifndef HAS_LIBC_OPEN
$(error You must define HAS_LIBC_OPEN)
endif
ifndef HAS_LIBC_CLOSE
$(error You must define HAS_LIBC_CLOSE)
endif
ifndef HAS_LIBC_LSEEK
$(error You must define HAS_LIBC_LSEEK)
endif
ifndef HAS_LIBC_FSTAT
$(error You must define HAS_LIBC_FSTAT)
endif

# Feature flags
override CFLAGS += -DLIBMY_USE_LIBC_FILE=$(USE_LIBC_FILE) -DLIBMY_HAS_LIBC_ALLOC=$(HAS_LIBC_ALLOC) -DLIBMY_HAS_LIBC_READ=$(HAS_LIBC_READ) -DLIBMY_HAS_LIBC_WRITE=$(HAS_LIBC_WRITE) -DLIBMY_HAS_LIBC_EXECVE=$(HAS_LIBC_EXECVE) -DLIBMY_HAS_LIBC_ISATTY=$(HAS_LIBC_ISATTY) -DLIBMY_HAS_LIBC_OPEN=$(HAS_LIBC_OPEN) -DLIBMY_HAS_LIBC_CLOSE=$(HAS_LIBC_CLOSE) -DLIBMY_HAS_LIBC_LSEEK=$(HAS_LIBC_LSEEK) -DLIBMY_HAS_LIBC_FSTAT=$(HAS_LIBC_FSTAT)

.PHONY: all clean fclean

.PREVIOUS: obj/%.o

HEADER_FILES := my my/assert my/ctype my/fcntl my/features my/getopt my/macros my/math my/my_string my/signal my/stdio my/stdlib my/string my/strings my/unistd my/cpp-like/algorithm my/cpp-like/iterator my/cpp-like/utility
HEADER_FILES := $(addprefix ../../include/, $(addsuffix .h, $(HEADER_FILES)))

all: ../libmy.a $(HEADER_FILES)

# The sources for libmy
# Stuff related to assert.h
SOURCE_FILES := assert/assert_fail

# Stuff related to ctype.h
SOURCE_FILES += ctype/isprint ctype/isupper ctype/islower ctype/isdigit ctype/isxdigit ctype/isalpha ctype/isalnum ctype/isspace ctype/toupper ctype/tolower

# Stuff related to fcntl.h
SOURCE_FILES += fcntl/open fcntl/creat

# Stuff related to getopt.h
SOURCE_FILES += getopt/getopt

# Stuff related to inttypes.h
SOURCE_FILES += inttypes/strtoimax inttypes/strtoumax

# Stuff related to math.h
SOURCE_FILES += math/fabs math/fpclassify math/signbit

# Stuff related to signal.h
SOURCE_FILES += signal/sigaddset

# Stuff related to stdio.h
SOURCE_FILES += stdio/putchar stdio/dputc stdio/dgetc stdio/dputs stdio/puts stdio/fclose stdio/g_my_standard_files stdio/fflush stdio/putc stdio/fputc stdio/fopen stdio/fileno stdio/ferror stdio/internal/file/normal/read stdio/internal/file/normal/write stdio/internal/file/normal/seek stdio/internal/file/normal/close stdio/internal/file/parse_mode stdio/internal/file/find_ptr stdio/internal/file/flush_skip_non_write stdio/internal/file/all_for_each stdio/internal/file/write_to_buffer stdio/internal/file/setup_write stdio/internal/file/make_buffer stdio/internal/file/determine_buffering stdio/internal/file/do_write stdio/internal/file/do_read stdio/internal/file/do_seek stdio/internal/file/cleanup

# Stuff related to printf
SOURCE_FILES += stdio/printf/printf stdio/printf/vprintf stdio/printf/dprintf stdio/printf/vdprintf stdio/printf/asprintf stdio/printf/vasprintf stdio/printf/formatter/append_number_base stdio/printf/formatter/utf32_char_to_utf8 stdio/printf/formatter/char stdio/printf/formatter/cstring stdio/printf/formatter/signed_integer stdio/printf/formatter/unsigned_integer stdio/printf/formatter/percent_sign stdio/printf/formatter/n stdio/printf/formatter/pointer stdio/printf/parse_conversion_info/parse_conversion_info stdio/printf/parse_conversion_info/parse_int stdio/printf/handle_invalid stdio/printf/padding

# Stuff related to stdlib.h
SOURCE_FILES += stdlib/qsort stdlib/qsort_r stdlib/realloc_size stdlib/strtol_base_str stdlib/strtol_base_str_part2 stdlib/strtol stdlib/strtoll stdlib/strtoul stdlib/strtoull stdlib/abs stdlib/abort stdlib/getenv_offset stdlib/getenv stdlib/setenv stdlib/unsetenv stdlib/free stdlib/malloc stdlib/calloc

# Stuff related to string.h
SOURCE_FILES += string/memset string/strlen string/strcpy string/strncpy string/strstr string/strcmp string/strcat string/strncat string/strchr string/strspn string/strcspn string/strnlen string/strdup string/strndup
ifeq ($(shell uname -p), x86_64)
	SOURCE_FILES += string/memcpy_x86_64 string/memmove_x86_64 string/memcmp_x86_64 string/memmem_x86_64 string/memchr_x86_64 string/strncmp_x86_64
else
	SOURCE_FILES += string/memcpy string/memmove string/memcmp string/memmem string/memchr string/strncmp
endif

# Stuff related to strings.h
SOURCE_FILES += strings/strcasecmp strings/bcopy

# Stuff related to sys/stat.h
SOURCE_FILES += sys/stat/fstat

# Stuff related to my_string
SOURCE_FILES += my_string/new_from_string my_string/new my_string/assign my_string/guarantee_can_expand my_string/append my_string/append_vprintf my_string/insert my_string/erase my_string/resize my_string/free

# Stuff related to unistd.h
SOURCE_FILES += unistd/execv unistd/execve unistd/execvp unistd/read unistd/write unistd/isatty unistd/close unistd/lseek

# x86-64-specific stuff
ifeq ($(shell uname -p), x86_64)
	SOURCE_FILES += sysdeps/is_running_under_valgrind_x86_64
endif

# Tests related to assert.h
TESTS_SOURCE_FILES := assert/assert

# Tests related to getopt.h
TESTS_SOURCE_FILES += getopt/getopt

# Tests related to stdlib.h
TESTS_SOURCE_FILES += stdlib/strtol_base_str stdlib/strtol stdlib/strtoul stdlib/abs stdlib/getenv stdlib/setenv stdlib/clearenv stdlib/putenv stdlib/qsort stdlib/qsort_r

# Tests related to string.h
TESTS_SOURCE_FILES += string/memcpy string/memmove string/memcmp string/memmem string/memchr string/strncmp

# Tests related to strings.h
TESTS_SOURCE_FILES += strings/bcopy

# Tests related to stdio.h
TESTS_SOURCE_FILES += stdio/printf/printf stdio/putc stdio/fileno stdio/FILE

# Tests related to math.h
TESTS_SOURCE_FILES += math/fabs math/signbit math/fpclassify

# Tests relatesd to unistd.h
TESTS_SOURCE_FILES += unistd/execvp

OBJECT_FILES := $(addprefix obj/src/, $(addsuffix .o, $(SOURCE_FILES)))
TESTS_OBJECT_FILES := $(addprefix obj/tests/, $(addsuffix .o, $(TESTS_SOURCE_FILES)))

# r is for inserting with replacement
# c is for creating the archive without a warning when it doesn't exist
# s is for writing an index into the archive
../libmy.a: $(OBJECT_FILES)
	$(AR) rcs $@ $^

tests_binary: $(TESTS_OBJECT_FILES) ../libmy.a
	rm -rf obj/src
	$(MAKE) ../libmy.a CFLAGS="$(CFLAGS) --coverage -DLIBMY_COVERAGE"
	$(CC) -o $@ $(CFLAGS) -L.. $(TESTS_OBJECT_FILES) -lcriterion -lmy --coverage -DLIBMY_COVERAGE

../../include/%.h: include/%.h
	@mkdir --parents ../../include/my/cpp-like
	cp $< $@

obj/%.o: %.s
	@mkdir --parents obj/src/string
	@mkdir --parents obj/src/sysdeps
	$(CC) -c $< -o $@ $(CFLAGS)

obj/%.o: %.c
	@mkdir --parents obj/src/assert
	@mkdir --parents obj/src/ctype
	@mkdir --parents obj/src/fcntl
	@mkdir --parents obj/src/getopt
	@mkdir --parents obj/src/inttypes
	@mkdir --parents obj/src/math
	@mkdir --parents obj/src/my_string
	@mkdir --parents obj/src/signal
	@mkdir --parents obj/src/stdio/printf/formatter
	@mkdir --parents obj/src/stdio/printf/parse_conversion_info
	@mkdir --parents obj/src/stdio/internal/file/normal
	@mkdir --parents obj/src/stdlib
	@mkdir --parents obj/src/string
	@mkdir --parents obj/src/strings
	@mkdir --parents obj/src/sys/stat
	@mkdir --parents obj/src/unistd
	$(CC) -c $< -o $@ $(CFLAGS)

obj/tests/%.o: ../../tests/libmy/%.c
	@mkdir --parents obj/tests/assert
	@mkdir --parents obj/tests/getopt
	@mkdir --parents obj/tests/math
	@mkdir --parents obj/tests/stdio/printf
	@mkdir --parents obj/tests/stdlib
	@mkdir --parents obj/tests/string
	@mkdir --parents obj/tests/strings
	@mkdir --parents obj/tests/unistd
	$(CC) -c $< -o $@ $(CFLAGS) --coverage -DLIBMY_COVERAGE -D_GNU_SOURCE # We sometimes need _GNU_SOURCE for tests, such as for memmem, get_current_dir_name or SNANL

# Include dependencies
include $(shell [ -d obj ] && find obj/ -type f -name '*.d')

# Remove all object files
clean:
	rm --recursive --force obj

# Remove all object, binary and other produced files
fclean: clean
	rm --recursive --force ../libmy.a tests_binary $(HEADER_FILES)
