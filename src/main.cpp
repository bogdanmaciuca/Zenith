#include <string>

#include "argparse.hpp"

#include "zenith/print.h"

constexpr const char* BUILD_DIR = "build";

int main(int argc, char** argv) {
    argparse::ArgumentParser arg_parser("zenith");
    arg_parser.add_argument("action").choices("build", "run", "clean");

    try {
        arg_parser.parse_args(argc, argv);
    }
    catch (const std::exception& e) {
        PrintError(e.what());
    }

    std::string action = arg_parser.get("build");

    if (action == "build") {

    }
    else if (action == "run") {

    }
    else if (action == "clean") {

    }
}

