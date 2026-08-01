#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_cache_simulator_menu(void)
{
    display_header("Help - Cache Replacement Simulator");

    printf("CACHE REPLACEMENT ALGORITHMS:\n");
    printf("    Cache replacement policies decide which memory page/block to evict\n");
    printf("    when a cache hit fails (cache miss) and the cache has reached full capacity.\n\n");

    printf("IMPLEMENTED EVICTION POLICIES:\n");
    printf("    • First-In, First-Out (FIFO): Evicts the oldest loaded block using a circular "
           "queue.\n");
    printf("    • Least Recently Used (LRU): Evicts the block with the oldest last access "
           "timestamp.\n");
    printf("    • Most Recently Used (MRU): Evicts the block accessed most recently (useful for "
           "looping scans).\n");
    printf("    • Least Frequently Used (LFU): Evicts the block with minimum hit count; features "
           "periodic aging/decay.\n");
    printf("    • Belady's Optimal (OPT): Lookahead policy evicting page accessed furthest in the "
           "future.\n");
    printf("    • Second-Chance (Clock): Circular buffer maintaining reference bits to\n"
           "      approximate LRU.\n\n");
    printf("    • Enhanced Second-Chance: Classifies blocks using (reference_bit, dirty_bit) "
           "tuples.\n\n");

    printf("TIME & SPACE COMPLEXITY CHEATSHEET:\n");
    printf("    +-------------------+----------------+----------------+----------------+\n");
    printf("    | Policy            | Lookup Time    | Eviction Time  | Space Overhead |\n");
    printf("    +-------------------+----------------+----------------+----------------+\n");
    printf("    | FIFO              | O(1)           | O(1)           | O(1)           |\n");
    printf("    | LRU               | O(1)           | O(1)           | O(N)           |\n");
    printf("    | MRU               | O(1)           | O(1)           | O(N)           |\n");
    printf("    | LFU (with Aging)  | O(1)           | O(N)           | O(N)           |\n");
    printf("    | Belady's OPT      | O(1)           | O(N * K)       | O(K)           |\n");
    printf("    | Clock             | O(1)           | O(N) worst     | O(N)           |\n");
    printf("    | Enhanced Clock    | O(1)           | O(N) worst     | O(N)           |\n");
    printf("    +-------------------+----------------+----------------+----------------+\n\n");

    printf("INTERACTIVE FEATURES & TUI ANIMATOR:\n");
    printf("    • Grid Visualization: Color-coded frames (Green = Hit, Red = Miss/Evict).\n");
    printf("    • Workload Benchmarking: Compares hit ratios across Zipfian, Looping, and Random "
           "traces.\n");
    printf("    • Step-by-Step Debugger: Step through page reference strings interactively.\n\n");

    printf("========================================================\n");
    printf("Press [ENTER] to return...\n");
    printf("========================================================\n");
    press_enter_to_continue();
}
