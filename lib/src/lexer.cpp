#include "zenith/lexer.h"

#include <string>

#include "zenith/ints.h"
#include "zenith/result.h"
#include "zenith/token.h"

namespace {
    std::string text;
    u32 idx;
    u32 line;
    u32 col;
    u32 tok_start;
}

bool AtEnd();
char Peek();
char Advance();
Token MakeToken(TokenType type);

Result<> InitLexer(const std::string& source) {
    text = std::move(source);
    idx = 0;
    line = 0;
    col = 0;

    return true;
}

Token LexToken() {
    if (AtEnd()) {
        return Token{ .type = TOK_EOF };
    }

    tok_start = idx;
    while (!AtEnd()) {
        char c = Advance();
        switch (c) {
            //case ' ', '\t', '\n': Advance() continue;
            case '(': return MakeToken(TOK_LEFT_PAREN);
            case ')': return MakeToken(TOK_RIGHT_PAREN);
            case '[': return MakeToken(TOK_LEFT_BRACKET);
            case ']': return MakeToken(TOK_RIGHT_BRACKET);
            case '{': return MakeToken(TOK_LEFT_BRACE);
            case '}': return MakeToken(TOK_RIGHT_BRACE);
            case '.': return MakeToken(TOK_DOT);
            case ',': return MakeToken(TOK_COMMA);
            case '+': return MakeToken(TOK_PLUS);
            case '-': return MakeToken(TOK_MINUS);
            case '*': return MakeToken(TOK_STAR);
            //case '/': return MakeToken(TOK_SLASH);
            default:
                //PrintError("");
                break;
        }
    }
    return Token{};
}

bool AtEnd() {
    return idx >= text.size();
}

char Peek() {
    return text[idx];
}

char Advance() {
    return text[idx++];
}

Token MakeToken(TokenType type) {
    return Token{
        .lexeme = text.substr(tok_start, idx),
        .line = line,
        .col = col,
        .type = type
    };
}

