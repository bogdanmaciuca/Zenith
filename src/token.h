#pragma once

#include <cstdint>
#include <string>

enum TokenType {
    TOK_KEYWORD,

    // Literals
    TOK_NUMBER,
    TOK_STRING,

};

struct Token {
    std::string lexeme;
    uint32_t line = 0;
    uint32_t col = 0;
    TokenType type;
};

