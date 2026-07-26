#include "bit_manipulation.h"
#include "display_header.h"
#include "safe_input.h"
#include <stdio.h>

void bit_manipulation_demo(void)
{
    int status, choice;

    while (1)
    {
        display_header("Bit Manipulation");

        status = safe_input_int(&choice,
                                "\nenter 1 for Basic Bit Operations demo"
                                "\nenter 2 for Count Set Bits demo"
                                "\nenter 3 for Power of Two Checker demo"
                                "\nenter 4 for XOR Swap demo"
                                "\nenter 5 for Rightmost Set Bit Operations demo"
                                "\nenter 6 for Reverse Bits demo"
                                "\nenter 7 for Find Unique Element (XOR) demo"
                                "\nenter 8 for Generate Subsets (Bitmasking) demo"
                                "\nenter choice (\'-1\' to exit, or \'help\') : ",
                                1, 8);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting bit_manipulation_demo.....\n");
            return;
        }

        if (status == 0)
            continue;

        switch (choice)
        {
            case 1:
                display_header("Basic Bit Operations");
                basic_bit_ops_demo();
                break;
            case 2:
                display_header("Count Set Bits");
                count_set_bits_demo();
                break;
            case 3:
                display_header("Power of Two Checker");
                power_of_two_demo();
                break;
            case 4:
                display_header("XOR Swap");
                xor_swap_demo();
                break;
            case 5:
                display_header("Rightmost Set Bit Operations");
                rightmost_set_bit_demo();
                break;
            case 6:
                display_header("Reverse Bits");
                reverse_bits_demo();
                break;
            case 7:
                display_header("Find Unique Element (XOR)");
                find_unique_demo();
                break;
            case 8:
                display_header("Generate Subsets (Bitmasking)");
                generate_subsets_demo();
                break;
        }
    }
}
