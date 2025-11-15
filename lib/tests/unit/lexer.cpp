#include "mctest/mctest.h"

int main() {
    MC_INIT();
    MC_EXPECT(false, "Shit!!!");
    MC_EXPECT(69 == 420, "NO WAY BROOOWWW");
    MC_EXIT();
}

