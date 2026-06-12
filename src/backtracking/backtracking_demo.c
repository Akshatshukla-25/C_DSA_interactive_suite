#include "backtracking.h"
#include "safe_input.h"
#include <stdio.h>

void backtracking_demo(void)
{
    int bt_status, bt_choice;
    while (1)
    {
        bt_status = safe_input_int(&bt_choice,
                                   "\n--- Backtracking Algorithms ---"
                                   "\nenter 1 for N-Queens problem (coming soon)"
                                   "\nenter 2 for Sudoku solver (coming soon)"
                                   "\nenter 3 for Knight's Tour (coming soon)"
                                   "\nenter choice : ",
                                   1, 3);

        if (bt_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Backtracking demo....\n");
            return;
        }

        if (bt_status == 0)
            continue;

        switch (bt_choice)
        {
            case 1:
                printf("\nN-Queens problem demo is coming soon!\n");
                break;
            case 2:
                printf("\nSudoku solver demo is coming soon!\n");
                break;
            case 3:
                printf("\nKnight's Tour demo is coming soon!\n");
                break;
        }
    }
}
