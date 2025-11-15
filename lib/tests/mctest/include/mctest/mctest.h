#pragma once

#define MC_INIT() \
    bool mc_test_failed = false;

#define MC_EXIT() \
    McExit(mc_test_failed == false ? 0 : 1);

#define MC_ASSERT(cond, message)                       \
    if (!(cond)) {                                       \
        McPrintAssertion(__FILE__, __LINE__, message, #cond); \
        McExit(1);                                       \
    }                                                  \

#define MC_EXPECT(cond, message) \
    if (!(cond)) { \
        McPrintExpected(__FILE__, __LINE__, message, #cond); \
        mc_test_failed = true; \
    } \

void McPrintAssertion(const char* file, int line, const char* message, const char* condition);
void McPrintExpected(const char* file, int line, const char* message, const char* condition);
void McExit(int code);

