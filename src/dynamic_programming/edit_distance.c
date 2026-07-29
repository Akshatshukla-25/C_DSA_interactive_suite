#include "dp_visualizer.h"
#include "dynamic_programming.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int min_of_three(int a, int b, int c)
{
    int min = a;
    if (b < min)
    {
        min = b;
    }
    if (c < min)
    {
        min = c;
    }
    return min;
}

int edit_distance(char* word1, char* word2, int m, int n)
{
    int** dp = malloc((m + 1) * sizeof(int*));
    if (dp == NULL)
    {
        printf("Memory allocation failed for DP table.\n");
        return -1;
    }
    for (int i = 0; i <= m; i++)
    {
        dp[i] = malloc((n + 1) * sizeof(int));
        if (dp[i] == NULL)
        {
            printf("Memory allocation failed for DP table row %d.\n", i);
            for (int j = 0; j < i; j++)
            {
                free(dp[j]);
            }
            free(dp);
            return -1;
        }
        for (int j = 0; j <= n; j++)
        {
            dp[i][j] = -1;
        }
    }

    // Compute DP table
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0)
            {
                dp[i][j] = j; // Min operations = j insertions
            }
            else if (j == 0)
            {
                dp[i][j] = i; // Min operations = i deletions
            }
            else if (word1[i - 1] == word2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min_of_three(dp[i][j - 1],    // Insert
                                            dp[i - 1][j],    // Remove
                                            dp[i - 1][j - 1] // Replace
                               );
            }

            // Visualize at each step
            visualize_dp_table_2d("Edit Distance DP Table", dp, m + 1, n + 1, word1, word2, i, j);
        }
    }

    // Final visualization
    visualize_dp_table_2d("Edit Distance Final DP Table", dp, m + 1, n + 1, word1, word2, m, n);

    int res = dp[m][n];

    for (int i = 0; i <= m; i++)
    {
        free(dp[i]);
    }
    free(dp);

    return res;
}
