#include "error_correction_algorithms.h"
#include "safe_input.h"
#include <stdio.h>
#include <string.h>

void hamming_demo(void)
{
    while (1)
    {
        char data[CHECKSUM_MAX_BITS + 1];

        int data_status = safe_input_binary_string(data, sizeof(data),
                                                   "\n\nHamming Code Demo\n"
                                                   "enter binary data bits or 'X' to exit:- ");

        if (data_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Hamming Code demo....");
            return;
        }

        if (data_status == 0)
        {
            continue;
        }

        char codeword[CHECKSUM_MAX_BITS + 16];
        hamming_generate(data, codeword);

        int k = (int)strlen(data);
        int n = (int)strlen(codeword);
        int r = n - k;

        printf("\nData bits (k)        : %d", k);
        printf("\nParity bits (r)      : %d", r);
        printf("\nCodeword length (n)  : %d", n);

        printf("\nHamming Code (P=parity, transmitted left to right):\n");
        for (int pos = 1; pos <= n; pos++)
        {
            if ((pos & (pos - 1)) == 0)
            {
                printf("P%d=%c ", pos, codeword[pos - 1]);
            }
            else
            {
                printf("D%d=%c ", pos, codeword[pos - 1]);
            }
        }

        printf("\nGenerated Hamming Code (%d,%d): %s\n", n, k, codeword);
    }
}
