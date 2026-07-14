#include "backtracking.h"
#include "config.h"
#include "safe_input.h"
#include <stdio.h>

#define MAX_N 8

void n_queens_demo(void)
{
    while (1)
    {
        int N;
        int status = safe_input_int(
            &N, "\nEnter the board size N (between 4 and 8), or -1 to exit: ", 4, MAX_N);
        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting N-Queens Solver...\n");
            return;
        }
        if (status == 0)
        {
            continue;
        }

        char board[MAX_N][MAX_N];
        for (int i = 0; i < MAX_N; i++)
            for (int j = 0; j < MAX_N; j++)
                board[i][j] = '.';

        printf("\nStarting N-Queens Solver...\n");
        dynamic_sleep();

        if (solve_n_queens_util(N, board, 0) == false)
        {
            printf("\nSolution does not exist for N=%d\n", N);
        }
        else
        {
            printf("\nSolution found successfully!\n");
        }
    }
}
