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

        printf("\n--- Visualizing Brian Kernighan's Algorithm ---\n");
        unsigned int un = (unsigned int)n;
        int count = 0;

        if (un == 0)
        {
            printf("  n       = ");
            print_binary_32(un);
            printf("  (0)\n");
        }

        while (un > 0)
        {
            unsigned int next_un = un & (un - 1);
            unsigned int flipped_bit = un ^ next_un;

            printf("Step %d:\n", count + 1);
            printf("  n       = ");
            print_binary_32_highlight(un, flipped_bit, "\033[1;31m");
            printf("  (%u)\n", un);

            printf("  n - 1   = ");
            print_binary_32(un - 1);
            printf("  (%u)\n", un - 1);

            printf("  n&(n-1) = ");
            print_binary_32_highlight(next_un, 0, NULL);
            printf("  (%u)\n\n", next_un);

            un = next_un;
            count++;

            if (un > 0)
            {
                press_enter_to_continue();
            }
        }
        printf("Final Count: %d\n", count);
        press_enter_to_continue();
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

        printf("\n--- Visualizing XOR Swap Step-by-Step ---\n");
        unsigned int ua = (unsigned int)a;
        unsigned int ub = (unsigned int)b;

        printf("Initial State:\n");
        printf("  A = ");
        print_binary_32(ua);
        printf("  (%d)\n", a);
        printf("  B = ");
        print_binary_32(ub);
        printf("  (%d)\n\n", b);
        press_enter_to_continue();

        printf("Step 1: A = A ^ B\n");
        unsigned int new_a = ua ^ ub;
        printf("  A = ");
        print_binary_32_highlight(ua, ua ^ new_a, "\033[1;33m");
        printf("\n  B = ");
        print_binary_32(ub);
        printf("\n  ---------------------------------------\n");
        printf("A^B = ");
        print_binary_32_highlight(new_a, ua ^ new_a, "\033[1;32m");
        printf("  (New A)\n\n");
        ua = new_a;
        press_enter_to_continue();

        printf("Step 2: B = A ^ B\n");
        unsigned int new_b = ua ^ ub;
        printf("  A = ");
        print_binary_32(ua);
        printf("\n  B = ");
        print_binary_32_highlight(ub, ub ^ new_b, "\033[1;33m");
        printf("\n  ---------------------------------------\n");
        printf("A^B = ");
        print_binary_32_highlight(new_b, ub ^ new_b, "\033[1;32m");
        printf("  (New B)\n\n");
        ub = new_b;
        press_enter_to_continue();

        printf("Step 3: A = A ^ B\n");
        new_a = ua ^ ub;
        printf("  A = ");
        print_binary_32_highlight(ua, ua ^ new_a, "\033[1;33m");
        printf("\n  B = ");
        print_binary_32(ub);
        printf("\n  ---------------------------------------\n");
        printf("A^B = ");
        print_binary_32_highlight(new_a, ua ^ new_a, "\033[1;32m");
        printf("  (New A)\n\n");
        ua = new_a;

        printf("Final Swapped State:\n");
        printf("  A = %d\n", (int)ua);
        printf("  B = %d\n", (int)ub);

        /* Actually swap the real variables so it's formally correct */
        xor_swap(&a, &b);
        press_enter_to_continue();
    }
}
