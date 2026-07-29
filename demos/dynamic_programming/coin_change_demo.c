#include "display_header.h"
#include "dynamic_programming.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void coin_change_demo(void)
{
    while (1)
    {
        display_header("Coin Change Demo");

        int choice;
        int status = safe_input_int(&choice,
                                    "\nenter 1 to solve Coin Change problem\n"
                                    "enter '-1' to exit: ",
                                    1, 1);

        if (status == INPUT_EXIT_SIGNAL)
        {
            return;
        }
        if (status == 0)
        {
            continue;
        }

        int n;
        int n_status =
            safe_input_int(&n, "\nEnter number of coin denominations (1 to 20): ", 1, 20);
        if (n_status == INPUT_EXIT_SIGNAL)
        {
            return;
        }
        if (n_status == 0)
        {
            continue;
        }

        int coins[20];
        int valid_coins = 1;
        for (int i = 0; i < n; i++)
        {
            char prompt[100];
            snprintf(prompt, sizeof(prompt), "Enter value for coin %d: ", i + 1);
            int coin_status = safe_input_int(&coins[i], prompt, 1, 1000);
            if (coin_status == INPUT_EXIT_SIGNAL)
            {
                valid_coins = 0;
                break;
            }
            if (coin_status == 0)
            {
                i--;
                continue;
            }
        }
        if (!valid_coins)
        {
            return;
        }

        int amount;
        int amount_status = safe_input_int(&amount, "\nEnter target amount (0 to 1000): ", 0, 1000);
        if (amount_status == INPUT_EXIT_SIGNAL)
        {
            return;
        }
        if (amount_status == 0)
        {
            continue;
        }

        printf("\n--- Minimum Coins ---\n");
        int min_coins = coin_change_min_coins(coins, n, amount);
        if (min_coins != -1)
        {
            printf("\nMinimum coins required: %d\n", min_coins);
        }
        else
        {
            printf("\nImpossible to make amount %d with the given coins.\n", amount);
        }

        printf("\n--- Total Ways ---\n");
        int ways = coin_change_ways(coins, n, amount);
        printf("\nTotal ways to make amount %d: %d\n", amount, ways);
    }
}
