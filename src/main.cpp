#include <string>
#include "print.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        PrintError("Not enough arguments.");
        return 1;
    }

    std::string arg = argv[1];
    if (arg == "build") {
        arg = argv[2];
        
    }
    else if (arg == "run") {
        // ...
    }
    return 0;
}

