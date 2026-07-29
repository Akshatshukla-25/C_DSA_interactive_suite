#include "dp_visualizer.h"
#include "dynamic_programming.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int coin_change_min_coins(int coins[], int n, int amount)
{
    if (amount < 0)
    {
        return -1;
    }
    long long* dp = malloc((amount + 1) * sizeof(long long));
    if (dp == NULL)
    {
        printf("Memory allocation failed for min coins DP array.\n");
        return -1;
    }

    dp[0] = 0;
    for (int i = 1; i <= amount; i++)
    {
        dp[i] = INT_MAX;
    }

    for (int i = 1; i <= amount; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= i)
            {
                long long res = dp[i - coins[j]];
                if (res != INT_MAX && res + 1 < dp[i])
                {
                    dp[i] = res + 1;
                }
            }
        }
        visualize_dp_table_1d("Coin Change (Min Coins) DP Array", dp, amount + 1, i);
    }
    visualize_dp_table_1d("Coin Change (Min Coins) Final DP Array", dp, amount + 1, amount);

    int ans = (dp[amount] == INT_MAX) ? -1 : (int)dp[amount];
    free(dp);
    return ans;
}

int coin_change_ways(int coins[], int n, int amount)
{
    if (amount < 0)
    {
        return 0;
    }
    long long* dp = calloc((amount + 1), sizeof(long long));
    if (dp == NULL)
    {
        printf("Memory allocation failed for coin ways DP array.\n");
        return 0;
    }

    dp[0] = 1;

    for (int j = 0; j < n; j++)
    {
        for (int i = coins[j]; i <= amount; i++)
        {
            dp[i] += dp[i - coins[j]];
            visualize_dp_table_1d("Coin Change (Total Ways) DP Array", dp, amount + 1, i);
        }
    }
    visualize_dp_table_1d("Coin Change (Total Ways) Final DP Array", dp, amount + 1, amount);

    int ans = (int)dp[amount];
    free(dp);
    return ans;
}
