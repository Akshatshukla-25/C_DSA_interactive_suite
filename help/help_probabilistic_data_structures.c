#include "clear_screen.h"
#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void help_probabilistic_data_structures_menu(void)
{
    while (1)
    {
        clear_screen();
        display_header("Help: Probabilistic Data Structures");

        printf("PROBABILISTIC DATA STRUCTURES OVERVIEW:\n");
        printf("    These data structures provide estimated answers to queries, trading\n");
        printf("    perfect accuracy for massive reductions in memory and time complexity.\n");
        printf("    They are essential in Big Data, streaming analytics, and caching.\n\n");

        printf("KEY STRUCTURES:\n");
        printf("    • Bloom Filters: Used to test whether an element is a member of a set.\n");
        printf("      False positive matches are possible, but false negatives are not.\n");
        printf("      Extremely space-efficient.\n");
        printf("    • HyperLogLog: Used to estimate the number of distinct elements\n");
        printf("      (cardinality) in a multiset. Can count billions of elements using\n");
        printf("      only a few kilobytes of memory.\n");
        printf("    • Count-Min Sketch: A frequency table of events in a stream of data.\n");
        printf("      Provides an upper bound on the frequency of a given event.\n\n");

        printf("COMMON APPLICATIONS:\n");
        printf("    • Web Caching: Preventing \"one-hit wonders\" from polluting the cache\n");
        printf("      by tracking access frequencies with a Count-Min Sketch.\n");
        printf("    • Database Optimization: Skipping disk lookups for non-existent keys\n");
        printf("      using a Bloom Filter (e.g., in Cassandra or RocksDB).\n");
        printf("    • Analytics: Counting unique visitors across distributed systems using\n");
        printf("      HyperLogLog.\n\n");

        printf("HOW TO RUN IN THIS SUITE:\n");
        printf("    1. Exit to the main menu and select option 20.\n");
        printf("    2. Choose a specific algorithm to interactively test.\n\n");

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
