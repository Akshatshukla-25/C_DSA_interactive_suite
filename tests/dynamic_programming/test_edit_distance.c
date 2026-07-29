#include "dynamic_programming.h"
#include "mock_printf.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define overrides to suppress history logging and DP table prints
#define printf mock_printf
#include "../../src/dynamic_programming/edit_distance.c"
#undef printf

void test_edit_distance_base_cases()
{
    reset_printf_buf();

    // Both empty
    assert(edit_distance("", "", 0, 0) == 0);

    // One empty
    assert(edit_distance("abc", "", 3, 0) == 3);
    assert(edit_distance("", "xyz", 0, 3) == 3);

    // Identical
    assert(edit_distance("hello", "hello", 5, 5) == 0);
}

void test_edit_distance_standard()
{
    reset_printf_buf();

    assert(edit_distance("kitten", "sitting", 6, 7) == 3);
    assert(edit_distance("horse", "ros", 5, 3) == 3);
}

void test_edit_distance_disjoint()
{
    reset_printf_buf();

    assert(edit_distance("abc", "xyz", 3, 3) == 3);
    assert(edit_distance("abcd", "efgh", 4, 4) == 4);
}

int main()
{
    test_edit_distance_base_cases();
    test_edit_distance_standard();
    test_edit_distance_disjoint();

    fprintf(stdout, "All Edit Distance tests passed successfully!\n");
    return 0;
}
