#include "zenith/lexer.h"

#include <string>

#include "zenith/ints.h"
#include "zenith/result.h"
#include "zenith/token.h"
#include "zenith/stack_queue.h"
#include "zenith/print.h"

constexpr i32 PARSER_LOOK_AHEAD = 2;

namespace {
    std::string text;
    u32 idx;
    u32 line;
    u32 col;
    u32 token_start;
    StackQueue<Token, PARSER_LOOK_AHEAD> token_queue;
}

bool AtEnd();
char Peek();
char Advance();
Token MakeToken(TokenType type);

Result<Token> LexToken();
Result<Token> LexDecimalNumber();
Result<Token> LexBinaryInt();
Result<Token> LexOctalInt();
Result<Token> LexHexInt();

Result<> InitLexer(const std::string& source) {
    text = std::move(source);
    idx = 0;
    line = 0;
    col = 0;
    token_start = 0;

    return true;
}

Result<Token> GetNextToken() {
    auto result = token_queue.Pop();
    if (!result) {
        PrintInternalError("GetNextToken(): " + result.ErrorStr());
        exit(1);
    }

    return LexToken();
}

Result<Token> LexToken() {
    if (AtEnd()) {
        return Token{ .type = TOK_EOF };
    }

    token_start = idx;
    while (!AtEnd()) {
        char c = Advance();
        switch (c) {
            // Whitespace
            //case ' ', '\t', '\n': Advance() continue;

            // Operators
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

            // Binary/octal/hex representation
            case '0':
                switch (char c = Advance()) {
                    case 'b': return LexBinaryInt();
                    case 'o': return LexOctalInt();
                    case 'x': return LexHexInt();
                    default:
                        return Error(std::string("Unexpected prefix: '0") + c + "'");
                }

            // Decimal representation
            case '1': case '2': case '3': case '4': case '5':
            case '6': case '7':  case '8': case '9':
                return LexDecimalNumber();
                break;

            // Invalid character
            default:
                return Error(std::string("Unexpected character: '") + c + "'");
                break;
        }
    }
    return Token{};
}

Result<Token> LexDecimalNumber() {
    // Consume digits until '.' or another character
    char c = Peek();
    while (isdigit(c) || c == '_') {
        c = Advance();
    }
    return Error("TODO!");
}

Result<Token> LexBinaryInt() {}
Result<Token> LexOctalInt() {}
Result<Token> LexHexInt() {}

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
        .lexeme = text.substr(token_start, idx),
        .line = line,
        .col = col,
        .type = type
    };
}

