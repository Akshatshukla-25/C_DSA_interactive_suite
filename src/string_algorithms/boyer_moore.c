#include "history_logger.h"
#include "safe_input.h"
#include "string_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void bad_char_heuristic(char* str, int size, int bad_char[256])
{
    for (int i = 0; i < 256; i++)
        bad_char[i] = -1;
    for (int i = 0; i < size; i++)
        bad_char[(unsigned char)str[i]] = i;
}

static void strong_suffix_heuristic(int* shift, int* bpos, char* pat, int m)
{
    int i = m, j = m + 1;
    bpos[i] = j;

    while (i > 0)
    {
        while (j <= m && pat[i - 1] != pat[j - 1])
        {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }
}

static void prefix_heuristic(int* shift, int* bpos, int m)
{
    int i, j;
    j = bpos[0];
    for (i = 0; i <= m; i++)
    {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = bpos[j];
    }
}

void boyer_moore_search(char* text, char* pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);

    if (m == 0 || n < m)
    {
        printf("Pattern not found in the text.\n");
        return;
    }

    int bad_char[256];
    bad_char_heuristic(pattern, m, bad_char);

    int* shift = (int*)calloc(m + 1, sizeof(int));
    int* bpos = (int*)malloc((m + 1) * sizeof(int));
    if (!shift || !bpos)
    {
        printf("Memory allocation failed.\n");
        free(shift);
        free(bpos);
        return;
    }

    strong_suffix_heuristic(shift, bpos, pattern, m);
    prefix_heuristic(shift, bpos, m);

    int s = 0;
    int found = 0;

    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j])
            j--;

        if (j < 0)
        {
            printf("Pattern found at index %d\n", s);
            found++;
            s += shift[0];
        }
        else
        {
            int bc_shift = j - bad_char[(unsigned char)text[s + j]];
            int gs_shift = shift[j + 1];
            s += (bc_shift > gs_shift) ? bc_shift : gs_shift;
        }
    }

    free(shift);
    free(bpos);

    if (found == 0)
    {
        printf("Pattern not found in the text.\n");
    }
    else
    {
        printf("Total occurrences found: %d\n", found);
    }
}

void boyer_moore_demo(void)
{
    while (1)
    {
        char text[100];
        char pattern[100];

        printf("\nBoyer-Moore String Matching Demo\n");

        int status_T =
            safe_input_string(text, "Enter text (no spaces, max 99 chars), or 'X' to exit: ");
        if (status_T == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting demo...\n");
            return;
        }

        int status_P =
            safe_input_string(pattern, "Enter pattern (no spaces, max 99 chars), or 'X' to exit: ");
        if (status_P == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting demo...\n");
            return;
        }

        clock_t start_t = clock();
        boyer_moore_search(text, pattern);
        clock_t end_t = clock();
        double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        printf("Total CPU time taken: %f seconds\n", total_t);

        add_to_history("Boyer-Moore Search", strlen(text), total_t);
    }
}
