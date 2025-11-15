#include <string>

#include "build.h"
#include "print.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        PrintError("Not enough arguments.");
        return 1;
    }

    std::string arg = argv[1];
    if (arg == "build") {
        arg = argv[2];
        auto result = Build(arg);
        if (result) {
            PrintInfo("Build succeeded.");
            return 0;
        }
        else {
            PrintInfo("Build failed: " + result.Error());
            return 1;
        }
    }
    else if (arg == "run") {
        // ...
        PrintInfo("TODO!");
        return 1;
    }

    return 0;
}

