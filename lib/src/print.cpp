#include "zenith/print.h"

#include <cstdio>
#include <string>

#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_CLEAR "\033[0m"

void PrintInfo(const std::string& message) {
    printf(COLOR_GREEN "Info" COLOR_CLEAR ": %s\n", message.c_str());
}

void PrintWarning(const std::string& message) {
    printf(COLOR_BLUE "Warning" COLOR_CLEAR ": %s\n", message.c_str());
}

void PrintError(const std::string& message) {
    printf(COLOR_RED "Error" COLOR_CLEAR ": %s\n", message.c_str());
}

