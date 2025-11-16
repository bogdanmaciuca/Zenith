#pragma once

#include <string>

#include "result.h"
#include "token.h"

Result<> InitLexer(const std::string& source);

Result<Token> GetNextToken();


