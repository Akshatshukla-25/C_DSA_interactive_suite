#include "backtracking.h"
#include "config.h"
#include "safe_input.h"
#include <stdio.h>

#define N 6

extern int placements;
extern int backtracks;
extern int original_grid_copy[N][N];

static int initial_grid[N][N] = {{1, 5, 3, 4, 6, 0}, {4, 6, 2, 0, 1, 3}, {2, 4, 5, 6, 3, 1},
                                 {0, 1, 6, 2, 4, 5}, {5, 3, 4, 1, 2, 6}, {6, 0, 1, 3, 5, 4}};

void sudoku_demo(void)
{
    while (1)
    {
        int choice;
        int status = safe_input_int(
            &choice, "\nEnter 1 to solve the predefined 6x6 Sudoku puzzle, or -1 to exit: ", 1, 1);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Sudoku Solver...\n");
            return;
        }
        if (status == 0)
        {
            continue;
        }

        int grid[N][N];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                grid[i][j] = initial_grid[i][j];
                original_grid_copy[i][j] = initial_grid[i][j];
            }
        }

        placements = 0;
        backtracks = 0;
        printf("\nStarting Sudoku Solver...\n");
        dynamic_sleep();
        print_sudoku_board(grid, original_grid_copy);

        if (solve_sudoku_util(grid, 0, 0))
        {
            printf("\nSudoku solved successfully!\n");
            printf("Total placements: %d\n", placements);
            printf("Backtracks: %d\n", backtracks);
        }
        else
        {
            printf("\nNo solution exists for this Sudoku.\n");
        }
    }
}
