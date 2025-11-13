#include "lexer.h"

#include <string>
#include "result.h"

#include <fstream>

Result<std::string> ReadFile(const std::string& path) {
    std::ifstream file(path, std::ios::ate);
    if (file.is_open())
        return Error("Could not open file");

    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string result(size, '\0');
    file.read(result.data(), size);

    return result;
}

