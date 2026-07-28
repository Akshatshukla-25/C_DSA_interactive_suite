#include "display_header.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void bloom_filter_demo(void);
void count_min_sketch_demo(void);
void hyperloglog_demo(void);

void probabilistic_ds_demo(void)
{
    while (1)
    {
        display_header("Probabilistic Data Structures Module");
        printf("1. Bloom Filter (Space-Efficient Set Membership)\n");
        printf("2. Count-Min Sketch (Sub-linear Frequency Estimation)\n");
        printf("3. HyperLogLog (Logarithmic Memory Cardinality Estimator)\n");
        printf("-1. Return to Main Menu\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", 1, 3);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Probabilistic Data Structures Module...\n");
            return;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                bloom_filter_demo();
                break;
            case 2:
                count_min_sketch_demo();
                break;
            case 3:
                hyperloglog_demo();
                break;
        }
    }
}
