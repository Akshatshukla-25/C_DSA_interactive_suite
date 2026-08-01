#include "clear_screen.h"
#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void help_spatial_indexing_menu(void)
{
    while (1)
    {
        clear_screen();
        display_header("Help: Spatial Indexing & Geometric Data Structures");

        printf("SPATIAL INDEXING OVERVIEW:\n");
        printf("    Spatial indexing data structures are designed to efficiently store and\n");
        printf("    query multidimensional data, such as geometric coordinates, rectangles,\n");
        printf("    or bounding boxes. They are heavily used in databases (PostGIS),\n");
        printf("    computer graphics, and geographic information systems (GIS).\n\n");

        printf("KEY STRUCTURES:\n");
        printf("    • R-Trees: Tree data structure used for spatial access methods, i.e.,\n");
        printf("      indexing multi-dimensional information. It groups nearby objects\n");
        printf("      and represents them with their minimum bounding rectangle (MBR).\n");
        printf("    • Quad-Trees: A tree data structure in which each internal node has\n");
        printf("      exactly four children. Used to partition a two-dimensional space\n");
        printf("      by recursively subdividing it into four quadrants or regions.\n");
        printf("    • k-d Trees: A space-partitioning data structure for organizing points\n");
        printf("      in a k-dimensional space. Useful for nearest neighbor searches.\n\n");

        printf("COMMON QUERIES:\n");
        printf("    • Nearest Neighbor Search: Finding the closest point(s) to a target.\n");
        printf("    • Range Search: Finding all points contained within a specified shape\n");
        printf("      (e.g., a circle or rectangle).\n");
        printf("    • Intersection Search: Finding all objects that intersect a given shape.\n\n");

        printf("HOW TO RUN IN THIS SUITE:\n");
        printf("    1. Exit to the main menu and select option 19.\n");
        printf("    2. Choose a specific spatial indexing algorithm to visualize.\n\n");

        printf("=================================================================\n");
        printf("Press [ENTER] to return to the main help menu...\n");
        printf("=================================================================\n");

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            /* Flush input buffer */
        }
        if (c == EOF)
        {
            exit(0);
        }
        return;
    }
}
