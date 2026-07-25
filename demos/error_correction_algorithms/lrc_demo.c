#include "error_correction_algorithms.h"
#include "safe_input.h"
#include <stdio.h>
#include <string.h>

#define LRC_MAX_ROWS 20
#define LRC_MAX_COLS 64

void lrc_demo(void)
{
    int rows;
    printf("\n=== LRC (Longitudinal Redundancy Check) ===\n");

    int result = safe_input_int(&rows, "Enter number of data words (1-20): ", 1, LRC_MAX_ROWS);
    if (result == -111)
    {
        printf("Exiting LRC demo...\n");
        return;
    }
    if (result == 0)
    {
        printf("Invalid input. Returning to main menu.\n");
        return;
    }

    char data[LRC_MAX_ROWS][LRC_MAX_COLS + 1];
    int cols = -1;

    printf("Enter binary data words (same length, e.g. 10110011):\n");
    for (int i = 0; i < rows; i++)
    {
        printf("  Word %d: ", i + 1);
        if (fgets(data[i], sizeof(data[i]), stdin) == NULL)
        {
            printf("Error reading input.\n");
            return;
        }

        trim_newline(data[i]);
        int len = (int)strlen(data[i]);

        if (len == 0)
        {
            printf("Error: word cannot be empty.\n");
            return;
        }

        for (int j = 0; j < len; j++)
        {
            if (data[i][j] != '0' && data[i][j] != '1')
            {
                printf("Error: word must contain only 0s and 1s.\n");
                return;
            }
        }

        if (cols == -1)
        {
            cols = len;
        }
        else if (len != cols)
        {
            printf("Error: all data words must have the same length.\n");
            return;
        }
    }

    const char* words[LRC_MAX_ROWS];
    for (int i = 0; i < rows; i++)
    {
        words[i] = data[i];
    }

    char lrc[LRC_MAX_COLS + 1];
    lrc_calculate(words, rows, cols, lrc);

    printf("\nTransmitted Block:\n");
    printf("------------------\n");
    for (int i = 0; i < rows; i++)
        printf("  Data word %2d : %s\n", i + 1, data[i]);
    printf("  LRC          : %s\n", lrc);
    printf("------------------\n");
    printf("LRC = %s\n", lrc);

    printf("\nColumn-by-column parity breakdown:\n");
    for (int j = 0; j < cols; j++)
    {
        int ones = 0;
        for (int i = 0; i < rows; i++)
            if (data[i][j] == '1')
                ones++;
        printf("  Col %2d : %d one(s) -> parity bit = %c\n", j + 1, ones, lrc[j]);
    }
}