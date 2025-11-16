#include "mctest/mctest.h"

#include "zenith/lexer.h"
#include "zenith/print.h"

int main() {
    MC_INIT();

    InitLexer("(){[]}[{]}*+=-");
    while (auto result = GetNextToken()) {
        MC_EXPECT(result, "Error occured");
        //PrintInfo(result.Value().lexeme);
    }

    MC_EXIT();
}

