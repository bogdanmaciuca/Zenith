#include "mctest/mctest.h"

#include <cstdio>
#include <cstdlib>

#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_CLEAR "\033[0m"

void McPrintAssertion(const char* file, int line, const char* message, const char* condition) {
    printf(
        COLOR_RED "\n=== Assertion failed! ===\n" COLOR_CLEAR
        "In " COLOR_BLUE "%s" COLOR_CLEAR ":\n" COLOR_BLUE "%d" COLOR_CLEAR ": %s: " COLOR_BLUE "%s\n" COLOR_CLEAR,
        file, line, message, condition
    );
}

void McPrintExpected(const char* file, int line, const char* message, const char* condition) {
    printf(
        COLOR_RED "\n=== Expected failed! ===\n" COLOR_CLEAR
        "In " COLOR_BLUE "%s" COLOR_CLEAR ":\n" COLOR_BLUE "%d" COLOR_CLEAR ": %s: " COLOR_BLUE "%s\n" COLOR_CLEAR,
        file, line, message, condition
    );
}

void McExit(int code) {
    exit(code);
}

