#include "backtracking.h"
#include "config.h"
#include "safe_input.h"
#include <stdio.h>

#define N 6

static int initial_maze[N][N] = {{1, 1, 1, 1, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 1, 1, 1, 1, 1},
                                 {0, 1, 0, 0, 0, 1}, {1, 1, 0, 1, 1, 1}, {1, 0, 0, 1, 0, 1}};

void rat_in_maze_demo(void)
{
    while (1)
    {
        int choice;
        int status = safe_input_int(
            &choice, "\nEnter 1 to solve the predefined 6x6 Rat in a Maze, or -1 to exit: ", 1, 1);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Rat in a Maze...\n");
            return;
        }
        if (status == 0)
        {
            continue;
        }

        int maze[N][N];
        int solution[N][N];

        // Initialize maze and empty solution matrix
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                maze[i][j] = initial_maze[i][j];
                solution[i][j] = 0;
            }
        }

        printf("\nStarting Rat in a Maze Solver...\n");
        dynamic_sleep();
        print_maze_state(maze, solution);

        if (solve_maze_util(maze, 0, 0, solution))
        {
            printf("\nSolution found successfully!\n");
        }
        else
        {
            printf("\nNo solution exists for this maze.\n");
        }
    }
}
