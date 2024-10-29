// test_main.cpp
#include <iostream>

extern void test_handle_record();
extern void test_finalize_sol();
extern void test_advance_sol();
extern void test_store_and_retrieve_sol_data();

int main() {
    std::cout << "Running Mars Rover Tests...\n";

    test_handle_record();
    test_finalize_sol();
    test_advance_sol();
    test_store_and_retrieve_sol_data();

    std::cout << "All tests passed successfully!\n";
    return 0;
}
