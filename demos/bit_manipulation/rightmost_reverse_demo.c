#include "bit_manipulation.h"
#include "safe_input.h"
#include <stdio.h>

void rightmost_set_bit_demo(void)
{
    while (1)
    {
        int n;
        int status = safe_input_int(&n,
                                    "\n\nRightmost Set Bit Operations demo"
                                    "\nenter an integer (between -1000 and 1000), "
                                    "enter '-1' to exit:- ",
                                    -1000, 1000);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting rightmost set bit demo.\n");
            return;
        }
        if (status == 0)
            continue;

        printf("\n--- Results for n = %d ---\n", n);
        printf("  get_rightmost_set_bit(%d)      = %d\n", n, get_rightmost_set_bit(n));
        printf("  turn_off_rightmost_set_bit(%d)  = %d\n", n, turn_off_rightmost_set_bit(n));
        printf("-------------------------------\n");
    }
}

void reverse_bits_demo(void)
{
    while (1)
    {
        int n;
        int status = safe_input_int(&n,
                                    "\n\nReverse Bits demo"
                                    "\nenter an unsigned integer (between 0 and 1000), "
                                    "enter '-1' to exit:- ",
                                    0, 1000);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting reverse bits demo.\n");
            return;
        }
        if (status == 0)
            continue;

        unsigned int result = reverse_bits((unsigned int)n);
        printf("\nreverse_bits(%d) = %u\n", n, result);
    }
}
