#include "dynamic_programming.h"
#include "mock_printf.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define overrides to suppress history logging and DP table prints
#define printf mock_printf
#include "../../src/dynamic_programming/coin_change.c"
#undef printf

void test_coin_change_base_cases()
{
    reset_printf_buf();
    int coins[] = {1, 2, 5};
    int n = 3;

    // Amount 0
    assert(coin_change_min_coins(coins, n, 0) == 0);
    assert(coin_change_ways(coins, n, 0) == 1);

    // Invalid amount
    assert(coin_change_min_coins(coins, n, -5) == -1);
    assert(coin_change_ways(coins, n, -5) == 0);
}

void test_coin_change_standard()
{
    reset_printf_buf();
    int coins[] = {1, 2, 5};
    int n = 3;

    assert(coin_change_min_coins(coins, n, 11) == 3); // 5+5+1
    // ways to make 5 with {1, 2, 5}:
    // 5
    // 2+2+1
    // 2+1+1+1
    // 1+1+1+1+1
    // Total = 4
    assert(coin_change_ways(coins, n, 5) == 4);
}

void test_coin_change_impossible()
{
    reset_printf_buf();
    int coins[] = {2};
    int n = 1;

    assert(coin_change_min_coins(coins, n, 3) == -1);
    assert(coin_change_ways(coins, n, 3) == 0);
}

void test_coin_change_greedy_failure()
{
    reset_printf_buf();
    int coins[] = {1, 3, 4};
    int n = 3;

    // To make 6: Greedy picks 4, then 1, 1 (3 coins). DP picks 3, 3 (2 coins).
    assert(coin_change_min_coins(coins, n, 6) == 2);
}

int main()
{
    test_coin_change_base_cases();
    test_coin_change_standard();
    test_coin_change_impossible();
    test_coin_change_greedy_failure();

    fprintf(stdout, "All Coin Change tests passed successfully!\n");
    return 0;
}
