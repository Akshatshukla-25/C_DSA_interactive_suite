#include "bit_manipulation.h"
#include "safe_input.h"
#include <stdio.h>

void find_unique_demo(void)
{
    while (1)
    {
        int n;
        int n_status =
            safe_input_int(&n,
                           "\n\nFind Unique Element (XOR) demo"
                           "\nenter the number of elements in the array (between 1 and 20), "
                           "enter '-1' to exit:- ",
                           1, 20);

        if (n_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting find unique demo.\n");
            return;
        }
        if (n_status == 0)
            continue;

        int arr[20];
        int valid = 1;

        for (int i = 0; i < n; i++)
        {
            printf("\nenter element %d (between -1000 and 1000), "
                   "enter '-1' to exit:- ",
                   i + 1);
            int elem_status = safe_input_int(&arr[i], NULL, -1000, 1000);

            if (elem_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting find unique demo.\n");
                return;
            }
            if (elem_status == 0)
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
            continue;

        printf("\nThe unique element is: %d\n", find_unique(arr, n));
    }
}

void generate_subsets_demo(void)
{
    while (1)
    {
        int n;
        int n_status =
            safe_input_int(&n,
                           "\n\nGenerate Subsets (Bitmasking) demo"
                           "\nenter the number of elements in the set (between 1 and 10), "
                           "enter '-1' to exit:- ",
                           1, 10);

        if (n_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting generate subsets demo.\n");
            return;
        }
        if (n_status == 0)
            continue;

        int arr[10];
        int valid = 1;

        for (int i = 0; i < n; i++)
        {
            printf("\nenter element %d (between -100 and 100), "
                   "enter '-1' to exit:- ",
                   i + 1);
            int elem_status = safe_input_int(&arr[i], NULL, -100, 100);

            if (elem_status == INPUT_EXIT_SIGNAL)
            {
                printf("\nExiting generate subsets demo.\n");
                return;
            }
            if (elem_status == 0)
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
            continue;

        printf("\nAll subsets (Power Set):\n");
        generate_subsets(arr, n);
    }
}
