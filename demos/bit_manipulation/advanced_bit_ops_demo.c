#include "bit_manipulation.h"
#include "safe_input.h"
#include <stdio.h>

void count_set_bits_demo(void)
{
    while (1)
    {
        int n;
        int status = safe_input_int(&n,
                                    "\n\nCount Set Bits demo"
                                    "\nenter an integer (between -1000 and 1000), "
                                    "enter '-1' to exit:- ",
                                    -1000, 1000);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting count set bits demo.\n");
            return;
        }
        if (status == 0)
            continue;

        printf("\ncount_set_bits(%d) = %d\n", n, count_set_bits(n));
    }
}

void power_of_two_demo(void)
{
    while (1)
    {
        int n;
        int status = safe_input_int(&n,
                                    "\n\nPower of Two Checker demo"
                                    "\nenter an integer (between -1000 and 1000), "
                                    "enter '-1' to exit:- ",
                                    -1000, 1000);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting power of two demo.\n");
            return;
        }
        if (status == 0)
            continue;

        if (is_power_of_two(n))
        {
            printf("\n%d IS a power of two.\n", n);
        }
        else
        {
            printf("\n%d is NOT a power of two.\n", n);
        }
    }
}

void xor_swap_demo(void)
{
    while (1)
    {
        int a;
        int a_status = safe_input_int(&a,
                                      "\n\nXOR Swap demo"
                                      "\nenter first integer (between -1000 and 1000), "
                                      "enter '-1' to exit:- ",
                                      -1000, 1000);

        if (a_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting xor swap demo.\n");
            return;
        }
        if (a_status == 0)
            continue;

        int b;
        int b_status = safe_input_int(&b,
                                      "\nenter second integer (between -1000 and 1000), "
                                      "enter '-1' to exit:- ",
                                      -1000, 1000);

        if (b_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting xor swap demo.\n");
            return;
        }
        if (b_status == 0)
            continue;

        printf("\nBefore swap: a = %d, b = %d\n", a, b);
        xor_swap(&a, &b);
        printf("After swap:  a = %d, b = %d\n", a, b);
    }
}
