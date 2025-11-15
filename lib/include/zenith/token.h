#pragma once

#include <string>

#include "ints.h"

constexpr const char* LEXEME_MUT       = "mut";
constexpr const char* LEXEME_CONST     = "const";
constexpr const char* LEXEME_STRUCT    = "struct";
constexpr const char* LEXEME_ALIAS     = "alias";
constexpr const char* LEXEME_TYPE      = "type";
constexpr const char* LEXEME_IF        = "if";
constexpr const char* LEXEME_ELSE      = "else";
constexpr const char* LEXEME_WHILE     = "while";
constexpr const char* LEXEME_FOR       = "for";
constexpr const char* LEXEME_IN        = "in";
constexpr const char* LEXEME_RETURN    = "return";
constexpr const char* LEXEME_BREAK     = "break";
constexpr const char* LEXEME_CONTINUE  = "continue";
constexpr const char* LEXEME_NAMESPACE = "namespace";
constexpr const char* LEXEME_USING     = "using";
constexpr const char* LEXEME_TRAIT     = "trait";
constexpr const char* LEXEME_IMPL      = "impl";
constexpr const char* LEXEME_SELF      = "Self";

enum TokenType {
    TOK_EOF,

    // Literals
    TOK_NUMBER,
    TOK_CHAR,
    TOK_STRING,

    // Keywords
    TOK_MUT, TOK_CONST,
    TOK_ALIAS, TOK_TYPE,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR, TOK_IN,
    TOK_RETURN,
    TOK_BREAK, TOK_CONTINUE,
    TOK_NAMESPACE, TOK_USING,
    TOK_TRAIT, TOK_IMPL,
    TOK_STRUCT, TOK_SELF,

    TOK_LEFT_PAREN, TOK_RIGHT_PAREN,
    TOK_LEFT_BRACKET, TOK_RIGHT_BRACKET,
    TOK_LEFT_BRACE, TOK_RIGHT_BRACE,

    // Arithmetic operators
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_MOD, TOK_POW,
    TOK_PLUS_PLUS, TOK_MINUS_MINUS,

    // Logical operators
    TOK_AND, TOK_OR, TOK_BANG,
    
    // Comparison operators
    TOK_EQUAL_EQUAL, TOK_BANG_EQUAL, TOK_LESS, TOK_GREATER, TOK_LESS_EQUAL, TOK_GREATER_EQUAL,

    // Bitwise operators
    TOK_AMPERSAND, TOK_PIPE, TOK_CARET, TOK_TILDE, TOK_LESS_LESS, TOK_GREATER_GREATER,

    // Assignment operator
    TOK_EQUAL,

    // Pointer operators
    // Already defined

    // Range operators
    TOK_RANGE_LESS, TOK_RANGE_GREATER, TOK_RANGE_EQUAL,

    // Scope operator
    TOK_COLON_COLON,

    // Others operators
    TOK_DOT, TOK_COMMA
};

struct Token {
    std::string lexeme = "";
    u32 line = 0;
    u32 col = 0;
    TokenType type;
};

