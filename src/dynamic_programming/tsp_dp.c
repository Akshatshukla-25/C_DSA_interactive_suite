#include "../bit_manipulation/bit_manipulation.h"
#include "dynamic_programming.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 999999999

int tsp_dp(int mask, int pos, int n, int** dist, int** memo)
{
    if (mask == (1 << n) - 1)
    {
        // Return to the starting city (city 0)
        return dist[pos][0] == 0 ? INF : dist[pos][0];
    }

    if (memo[mask][pos] != -1)
    {
        return memo[mask][pos];
    }

    int ans = INF;

    for (int city = 0; city < n; city++)
    {
        if (!check_bit(mask, city) && dist[pos][city] != 0)
        {
            int new_mask = set_bit(mask, city);
            int new_ans = dist[pos][city] + tsp_dp(new_mask, city, n, dist, memo);
            if (new_ans < ans)
            {
                ans = new_ans;
            }
        }
    }

    return memo[mask][pos] = ans;
}

int* reconstruct_tsp_path(int n, int** dist, int** memo, int min_cost)
{
    if (min_cost >= INF)
    {
        return NULL; // No valid path
    }

    int* path = malloc(sizeof(int) * (n + 1));
    if (path == NULL)
    {
        return NULL;
    }

    int mask = 1; // City 0 visited
    int pos = 0;
    path[0] = 0;

    for (int i = 1; i < n; i++)
    {
        int next_city = -1;
        for (int city = 0; city < n; city++)
        {
            if (!check_bit(mask, city) && dist[pos][city] != 0)
            {
                int new_mask = set_bit(mask, city);
                int cost_from_here = dist[pos][city] + tsp_dp(new_mask, city, n, dist, memo);
                if (cost_from_here == memo[mask][pos])
                {
                    next_city = city;
                    break;
                }
            }
        }

        if (next_city == -1)
        {
            free(path);
            return NULL;
        }

        path[i] = next_city;
        mask = set_bit(mask, next_city);
        pos = next_city;
    }

    path[n] = 0; // Return to start
    return path;
}

int solve_tsp(int n, int** dist, int** path_out)
{
    if (n <= 0)
    {
        if (path_out != NULL)
        {
            *path_out = NULL;
        }
        return 0;
    }
    if (n == 1)
    {
        if (path_out != NULL)
        {
            *path_out = malloc(sizeof(int) * 2);
            if (*path_out != NULL)
            {
                (*path_out)[0] = 0;
                (*path_out)[1] = 0;
            }
        }
        return 0;
    }

    int num_states = 1 << n;
    int** memo = malloc(sizeof(int*) * num_states);
    if (memo == NULL)
    {
        return INF;
    }

    for (int i = 0; i < num_states; i++)
    {
        memo[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
            memo[i][j] = -1;
        }
    }

    int min_cost = tsp_dp(1, 0, n, dist, memo);

    if (path_out != NULL)
    {
        *path_out = reconstruct_tsp_path(n, dist, memo, min_cost);
    }

    for (int i = 0; i < num_states; i++)
    {
        free(memo[i]);
    }
    free(memo);

    return min_cost;
}
