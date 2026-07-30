#include "display_header.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void kd_tree_demo(void);
void quadtree_demo(void);
void rtree_demo(void);

void spatial_indexing_demo(void)
{
    while (1)
    {
        display_header("Spatial & Multi-Dimensional Indexing Module");
        printf("1. k-d Tree (Point Indexing & k-Nearest Neighbor)\n");
        printf("2. QuadTree (2D Spatial Partitioning)\n");
        printf("3. R-Tree (Spatial Bounding Box Index)\n");
        printf("-1. Return to Main Menu\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", 1, 3);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Spatial Indexing Module...\n");
            return;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                kd_tree_demo();
                break;
            case 2:
                quadtree_demo();
                break;
            case 3:
                rtree_demo();
                break;
        }
    }
}
