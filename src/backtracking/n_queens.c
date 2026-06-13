#include "backtracking.h"
#include "safe_input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#define CLEAR_SCREEN() system("cls")
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#define CLEAR_SCREEN() system("clear")
#endif

#define MAX_N 8

static void print_board(int N, char board[MAX_N][MAX_N])
{
    CLEAR_SCREEN();
    printf("\n--- N-Queens Visualization ---\n\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf(" %c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    SLEEP_MS(200);
}

static bool is_safe(int N, char board[MAX_N][MAX_N], int row, int col)
{
    int i, j;

    // Check this row on left side
    for (i = 0; i < col; i++)
        if (board[row][i] == 'Q')
            return false;

    // Check upper diagonal on left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 'Q')
            return false;

    // Check lower diagonal on left side
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j] == 'Q')
            return false;

    return true;
}

static bool solve_n_queens_util(int N, char board[MAX_N][MAX_N], int col)
{
    // Base case: If all queens are placed
    if (col >= N)
        return true;

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < N; i++)
    {
        if (is_safe(N, board, i, col))
        {
            // Place the queen
            board[i][col] = 'Q';
            print_board(N, board);

            // Recur to place rest of the queens
            if (solve_n_queens_util(N, board, col + 1))
                return true;

            // If placing queen here doesn't lead to a solution, backtrack
            board[i][col] = '.'; 
            print_board(N, board);
        }
    }

    // If the queen cannot be placed in any row in this column, return false
    return false;
}

void n_queens_demo(void)
{
    int N;
    int status = safe_input_int(&N, "\nEnter the board size N (between 4 and 8): ", 4, MAX_N);
    if (status == INPUT_EXIT_SIGNAL)
    {
        return;
    }

    char board[MAX_N][MAX_N];
    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            board[i][j] = '.';

    printf("\nStarting N-Queens Solver...\n");
    SLEEP_MS(1000);

    if (solve_n_queens_util(N, board, 0) == false)
    {
        printf("\nSolution does not exist for N=%d\n", N);
    }
    else
    {
        printf("\nSolution found successfully!\n");
    }
}
