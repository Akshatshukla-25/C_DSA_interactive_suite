#include "../utils/config.h"
#include "clear_screen.h"
#include "history_logger.h"
#include "safe_input.h"
#include "string_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Shift {
    int index;
    char* str;
} Shift;

static int shift_cmp(const void* a, const void* b)
{
    return strcmp(((Shift*)a)->str, ((Shift*)b)->str);
}

char* bwt_encode(char* text, int* src_idx)
{
    int n = strlen(text);
    char* text_sentinel = (char*)malloc((n + 2) * sizeof(char));
    if (!text_sentinel)
        return NULL;
    strcpy(text_sentinel, text);
    text_sentinel[n] = '$';
    text_sentinel[n + 1] = '\0';
    int len = n + 1;

    Shift* shifts = (Shift*)malloc(len * sizeof(Shift));
    if (!shifts)
    {
        free(text_sentinel);
        return NULL;
    }

    for (int i = 0; i < len; i++)
    {
        shifts[i].index = i;
        shifts[i].str = (char*)malloc((len + 1) * sizeof(char));
        for (int j = 0; j < len; j++)
        {
            shifts[i].str[j] = text_sentinel[(i + j) % len];
        }
        shifts[i].str[len] = '\0';
    }

    qsort(shifts, len, sizeof(Shift), shift_cmp);

    char* bwt = (char*)malloc((len + 1) * sizeof(char));
    if (bwt)
    {
        for (int i = 0; i < len; i++)
        {
            bwt[i] = shifts[i].str[len - 1];
            if (shifts[i].index == 0)
            {
                if (src_idx)
                    *src_idx = i;
            }
        }
        bwt[len] = '\0';
    }

    for (int i = 0; i < len; i++)
    {
        free(shifts[i].str);
    }
    free(shifts);
    free(text_sentinel);

    return bwt;
}

char* bwt_decode(char* bwt)
{
    int n = strlen(bwt);
    if (n == 0)
        return NULL;

    int count[256] = {0};
    for (int i = 0; i < n; i++)
        count[(unsigned char)bwt[i]]++;

    int pos[256] = {0};
    int sum = 0;
    for (int i = 0; i < 256; i++)
    {
        pos[i] = sum;
        sum += count[i];
    }

    int* lf = (int*)malloc(n * sizeof(int));
    int char_count[256] = {0};
    if (!lf)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        unsigned char c = bwt[i];
        lf[i] = pos[c] + char_count[c];
        char_count[c]++;
    }

    int curr = 0;
    for (int i = 0; i < n; i++)
    {
        if (bwt[i] == '$')
        {
            curr = i;
            break;
        }
    }

    char* orig = (char*)malloc((n + 1) * sizeof(char));
    if (orig)
    {
        orig[n] = '\0';
        for (int i = n - 1; i >= 0; i--)
        {
            orig[i] = bwt[curr];
            curr = lf[curr];
        }
    }

    free(lf);
    return orig;
}

void bwt_visualization(char* text)
{
    if (!is_instant())
    {
        clear_screen();
    }

    printf("\n--- Burrows-Wheeler Transform Encoding ---\n");
    printf("Original Text: %s\n", text);

    int src_idx = -1;
    char* bwt = bwt_encode(text, &src_idx);
    if (!bwt)
        return;

    printf("Sentinel Text: %s$\n", text);
    printf("BWT Output   : %s\n", bwt);
    dynamic_sleep();

    printf("\n--- Inverse BWT Decoding ---\n");
    char* decoded = bwt_decode(bwt);
    if (decoded)
    {
        printf("Decoded Text : %s\n", decoded);
        free(decoded);
    }
    free(bwt);
}

void bwt_demo(void)
{
    while (1)
    {
        char text[100];

        printf("\nBurrows-Wheeler Transform Demo\n");

        int status_T =
            safe_input_string(text, "Enter text (no spaces, max 99 chars), or 'X' to exit: ");
        if (status_T == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting demo...\n");
            return;
        }

        clock_t start_t = clock();
        bwt_visualization(text);
        clock_t end_t = clock();
        double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

        printf("\nTotal CPU time taken: %f seconds\n", total_t);
        add_to_history("BWT Transform", strlen(text), total_t);
    }
}
