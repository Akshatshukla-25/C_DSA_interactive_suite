#include "error_correction_algorithms.h"
#include "safe_input.h"
#include <stdio.h>
#include <string.h>

void checksum_demo(void)
{
    while (1)
    {
        int k;
        int k_status =
            safe_input_int(&k,
                           "\n\nchecksum (sender side)\nenter the block size k in bits (1 to 16), "
                           "or -1 to exit:- ",
                           1, 16);

        if (k_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting checksum demo....");
            return;
        }
        if (k_status == 0)
        {
            continue;
        }

        char data[CHECKSUM_MAX_BITS + 1];
        int data_status = safe_input_binary_string(
            data, sizeof(data), "enter the binary data (digits 0/1 only), or 'X' to exit:- ");

        if (data_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting checksum demo....");
            return;
        }
        if (data_status == 0)
        {
            continue;
        }

        int len = (int)strlen(data);
        int mask = (1 << k) - 1; // keeps only the low k bits

        int sum = checksum_block_sum(data, len, k);
        int checksum = (~sum) & mask; // one's complement of the final sum, kept to k bits

        printf("\nfinal sum       = ");
        checksum_print_binary(sum, k);
        printf("\nchecksum (~sum) = ");
        checksum_print_binary(checksum, k);
        printf("\n\nthe sender appends this checksum to the data before transmission.\n");
    }
}
