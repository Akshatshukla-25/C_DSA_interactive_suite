#include "dynamic_programming.h"
#include "safe_input.h"
#include <stdio.h>

void dynamic_programming_demo(void)
{
    int dp_status, dp_choice;
    while (1)
    {
        dp_status = safe_input_int(&dp_choice,
                                   "\n--- Dynamic Programming Algorithms ---"
                                   "\nenter 1 for Fibonacci (coming soon)"
                                   "\nenter 2 for 0/1 Knapsack (coming soon)"
                                   "\nenter 3 for Longest Common Subsequence (coming soon)"
                                   "\nenter choice : ",
                                   1, 3);

        if (dp_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting dynamic_programming_demo....\n");
            return;
        }

        if (dp_status == 0)
            continue;

        switch (dp_choice)
        {
            case 1:
                printf("\nFibonacci algorithm demo is coming soon!\n");
                break;
            case 2:
                printf("\n0/1 Knapsack algorithm demo is coming soon!\n");
                break;
            case 3:
                printf("\nLongest Common Subsequence algorithm demo is coming soon!\n");
                break;
        }
    }
}
