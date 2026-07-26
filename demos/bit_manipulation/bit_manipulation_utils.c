#include "bit_manipulation.h"
#include <stdio.h>

/**
 * Prints a 32-bit integer in grouped binary format: "0000 0000 ... 0000"
 * Highlights the bits specified by highlight_mask using ANSI color_code.
 */
void print_binary_32_highlight(unsigned int n, unsigned int highlight_mask, const char* color_code)
{
    for (int i = 31; i >= 0; i--)
    {
        int bit = (n >> i) & 1;
        int is_highlighted = (highlight_mask >> i) & 1;

        if (is_highlighted && color_code != NULL)
        {
            printf("%s%d\033[0m", color_code, bit);
        }
        else
        {
            printf("%d", bit);
        }

        if (i % 4 == 0 && i != 0)
        {
            printf(" ");
        }
    }
}

/**
 * Basic version that prints without highlights
 */
void print_binary_32(unsigned int n)
{
    print_binary_32_highlight(n, 0, NULL);
}
