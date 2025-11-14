#include "print.h"

#include <cstdio>

#define COLOR_RED "\033[0;31m"
#define COLOR_CLEAR "\033[0m"

void PrintError(const std::string& message) {
    printf(COLOR_RED "Error" COLOR_CLEAR ": %s\n", message.c_str());
}

