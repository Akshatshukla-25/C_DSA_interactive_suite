#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_dynamic_programming_menu(void)
{
    display_header("Help - Dynamic Programming");

    printf("--- DP FUNDAMENTALS (MEMOIZATION VS TABULATION) ---\n\n");
    printf("WHAT DYNAMIC PROGRAMMING SOLVES:\n");
    printf("    Dynamic Programming (DP) is used when a problem can be split into\n");
    printf("    smaller subproblems whose answers can be reused. It is ideal when the\n");
    printf("    same states appear repeatedly during the search.\n\n");
    printf("CORE PROPERTIES:\n");
    printf("    • Optimal substructure: an optimal solution can be built from optimal\n");
    printf("      solutions to subproblems.\n");
    printf("    • Overlapping subproblems: the same subproblem is solved many times\n");
    printf("      in a naive recursive solution.\n\n");
    printf("MEMOIZATION VS TABULATION:\n");
    printf("    Memoization (top-down):\n");
    printf("      - Start with recursion and cache results after first computation.\n");
    printf("      - Best when not every state needs to be visited.\n");
    printf("      - Easier to write when the recursive relation is already clear.\n\n");
    printf("    Tabulation (bottom-up):\n");
    printf("      - Build the answer iteratively from the smallest states upward.\n");
    printf("      - Best when the state order is easy to determine.\n");
    printf("      - Usually avoids recursion depth and often has tighter control over\n");
    printf("        memory layout.\n\n");
    printf("WHEN TO USE EACH:\n");
    printf("    • Use memoization when the state space is sparse or the recursive\n");
    printf("      structure is easier to express than an iterative table.\n");
    printf("    • Use tabulation when you know the dependency order and want a\n");
    printf("      predictable iterative implementation.\n\n");
    printf("TIME & SPACE PATTERN:\n");
    printf("    • Naive recursion on DP problems is often exponential.\n");
    printf("    • Memoization and tabulation usually reduce the runtime to polynomial\n");
    printf("      time by solving each state once.\n");
    printf("    • Space is typically O(state count) for the table, plus recursion\n");
    printf("      stack only in memoized top-down solutions.\n\n");

    printf("--- FIBONACCI & 0/1 KNAPSACK ---\n\n");
    printf("1) FIBONACCI SEQUENCE\n");
    printf("PROBLEM DEFINITION:\n");
    printf("    Compute F(n), where F(n) = F(n-1) + F(n-2), F(0)=0, F(1)=1.\n\n");
    printf("RECURRENCE:\n");
    printf("    F(n) = F(n-1) + F(n-2)\n");
    printf("    Base cases: F(0)=0, F(1)=1\n\n");
    printf("DP TABLE WALKTHROUGH:\n");
    printf("    • Memoization stores previously computed F(i) values in a cache.\n");
    printf("    • Tabulation fills dp[0], dp[1], then dp[i] = dp[i-1] + dp[i-2].\n");
    printf("    • Each entry depends only on the two previous entries.\n\n");
    printf("COMPLEXITY:\n");
    printf("    • Naive recursion: O(2^n) time, O(n) stack.\n");
    printf("    • Memoization: O(n) time, O(n) space.\n");
    printf("    • Tabulation: O(n) time, O(n) space, reducible to O(1) auxiliary\n");
    printf("      space with two variables.\n\n");
    printf("2) 0/1 KNAPSACK\n");
    printf("PROBLEM DEFINITION:\n");
    printf("    Choose a subset of items with weights wt[i] and values val[i] so the\n");
    printf("    total weight does not exceed capacity W, while maximizing total value.\n\n");
    printf("RECURRENCE:\n");
    printf("    dp[i][w] = max(dp[i-1][w], val[i-1] + dp[i-1][w-wt[i-1]])\n");
    printf("    when wt[i-1] <= w, otherwise dp[i][w] = dp[i-1][w].\n\n");
    printf("DP TABLE WALKTHROUGH:\n");
    printf("    • Rows represent how many items are considered.\n");
    printf("    • Columns represent the current capacity from 0 to W.\n");
    printf("    • The first row and first column are zero because no items or no\n");
    printf("      capacity means zero value.\n");
    printf("    • Each cell compares taking the item vs skipping it.\n\n");
    printf("COMPLEXITY:\n");
    printf("    • Naive recursion: O(2^n) time.\n");
    printf("    • DP table: O(nW) time, O(nW) space.\n");
    printf("    • A 1D optimization can reduce the space to O(W).\n\n");

    printf("--- LCS & MATRIX CHAIN MULTIPLICATION ---\n\n");
    printf("3) LONGEST COMMON SUBSEQUENCE (LCS)\n");
    printf("PROBLEM DEFINITION:\n");
    printf("    Find the longest sequence that appears in both strings in the same\n");
    printf("    relative order, but not necessarily contiguously.\n\n");
    printf("RECURRENCE:\n");
    printf("    If X[i-1] == Y[j-1], dp[i][j] = 1 + dp[i-1][j-1].\n");
    printf("    Otherwise dp[i][j] = max(dp[i-1][j], dp[i][j-1]).\n\n");
    printf("DP TABLE WALKTHROUGH:\n");
    printf("    • Rows index prefixes of the first string.\n");
    printf("    • Columns index prefixes of the second string.\n");
    printf("    • The first row and column are zeros for empty-string prefixes.\n");
    printf("    • The traceback from dp[m][n] reconstructs the subsequence.\n\n");
    printf("COMPLEXITY:\n");
    printf("    • Naive recursion: exponential time.\n");
    printf("    • DP: O(mn) time, O(mn) space.\n\n");
    printf("4) MATRIX CHAIN MULTIPLICATION (MCM)\n");
    printf("PROBLEM DEFINITION:\n");
    printf("    Given matrices A1..An with compatible dimensions, find the parenthesization\n");
    printf("    that minimizes scalar multiplications.\n\n");
    printf("RECURRENCE:\n");
    printf("    m[i][j] = min over k in [i, j-1] of\n");
    printf("              m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]\n\n");
    printf("DP TABLE WALKTHROUGH:\n");
    printf("    • dp[i][j] stores the best cost for multiplying Ai..Aj.\n");
    printf("    • The table is filled by increasing chain length.\n");
    printf("    • The split table records the k value that produced the best cost.\n\n");
    printf("COMPLEXITY:\n");
    printf("    • Naive recursion: exponential.\n");
    printf("    • DP: O(n^3) time, O(n^2) space.\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}