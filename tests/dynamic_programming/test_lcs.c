#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_programming.h"
#include "mock_printf.h"

// Define overrides to suppress history logging and DP table prints
#define printf mock_printf
#include "../../src/dynamic_programming/lcs.c"
#undef printf

void test_lcs_base_cases(void)
{
    reset_printf_buf();
    char* X = "";
    char* Y = "ABC";
    assert(lcs(X, Y, 0, 3) == 0);
    assert(strstr(g_printf_buf, "Traceback: Longest Common Subsequence is \"\"") != NULL);

    reset_printf_buf();
    assert(lcs(Y, X, 3, 0) == 0);
    assert(strstr(g_printf_buf, "Traceback: Longest Common Subsequence is \"\"") != NULL);
}

void test_lcs_normal_case(void)
{
    reset_printf_buf();
    char* X = "ABCDGH";
    char* Y = "AEDFHR";
    assert(lcs(X, Y, 6, 6) == 3);
    assert(strstr(g_printf_buf, "Traceback: Longest Common Subsequence is \"ADH\"") != NULL);
}

void test_lcs_no_common(void)
{
    reset_printf_buf();
    char* X = "ABC";
    char* Y = "XYZ";
    assert(lcs(X, Y, 3, 3) == 0);
    assert(strstr(g_printf_buf, "Traceback: Longest Common Subsequence is \"\"") != NULL);
}

void test_lcs_identical(void)
{
    reset_printf_buf();
    char* X = "abcdef";
    char* Y = "abcdef";
    assert(lcs(X, Y, 6, 6) == 6);
    assert(strstr(g_printf_buf, "Traceback: Longest Common Subsequence is \"abcdef\"") != NULL);
}

int main(void)
{
    test_lcs_base_cases();
    test_lcs_normal_case();
    test_lcs_no_common();
    test_lcs_identical();

    fprintf(stdout, "All LCS tests passed successfully!\n");
    return 0;
}
