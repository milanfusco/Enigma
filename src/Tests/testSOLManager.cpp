// test_sol_manager.cpp
#include <cassert>
#include "Data/SOLManager.h"

void test_advance_sol() {
    SOLManager solManager;
    assert(solManager.getCurrentSOL() == 1);

    solManager.advanceSOL();
    assert(solManager.getCurrentSOL() == 2);
}
