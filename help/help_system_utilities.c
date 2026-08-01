#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_system_utilities_menu(void)
{
    display_header("Help: System Utilities, Telemetry & Serialization");

    printf("--- TELEMETRY & MEMORY PROFILER ENGINE ---\n\n");
    printf("1. SORTING TELEMETRY DASHBOARD\n");
    printf("CONCEPT:\n");
    printf("   Tracks real-time algorithmic operations, comparisons, swaps, and execution\n"
           "   timers.\n");
    printf("   - Features: Real-time swap counters, time-series metrics, comparative\n"
           "     dashboards.\n\n");
    printf("2. MEMORY INSPECTOR & PROFILER\n");
    printf("CONCEPT:\n");
    printf("   Intercepts malloc/free allocations to audit heap usage and detect memory leaks.\n");
    printf("   - Features: Active allocation tracking, byte leakage alerts, pointer\n"
           "     inspection.\n\n");

    printf("--- STATE SERIALIZATION & BINARY DISK PERSISTENCE ---\n\n");
    printf("STATE SERIALIZATION & DESERIALIZATION\n");
    printf("CONCEPT:\n");
    printf("   Serializes live in-memory data structures (BST, AVL Trees, Graphs) to binary\n");
    printf("   payload files on disk and restores exact state during application execution.\n");
    printf("   - Supported Structures: Binary Search Trees, AVL Trees, Weighted Graphs.\n");
    printf("   - Data Integrity: Checksum-verified binary payloads.\n\n");

    printf("--- DEVELOPER DIAGNOSTICS (FUZZING, BIG-O, EXPORTER) ---\n\n");
    printf("1. STOCHASTIC FUZZ TESTING ENGINE\n");
    printf("CONCEPT:\n");
    printf("   Bombards algorithms with randomized, edge-case inputs to verify robust\n"
           "   constraint handling and uncover unexpected segfaults.\n\n");
    printf("2. EMPIRICAL BIG-O VERIFIER\n");
    printf("CONCEPT:\n");
    printf("   Runs algorithms against scaling dataset sizes (e.g., 10^2 to 10^6) and curves\n");
    printf("   the runtime mathematically to empirically prove O(N log N), O(N^2), etc.\n\n");
    printf("3. STANDALONE FILE EXPORTER\n");
    printf("CONCEPT:\n");
    printf("   Exports internal arrays, graphs, or trees to .csv or .md files for external\n");
    printf("   analysis and cross-referencing.\n\n");

    printf("--- ALGORITHM BENCHMARKING & PROFILING ---\n\n");
    printf("ALGORITHM BENCHMARKING & PROFILING\n");
    printf("CONCEPT:\n");
    printf("   Measures and compares execution time, memory usage, or operational\n");
    printf("   efficiency across different algorithms under uniform conditions.\n\n");
    printf("CONFIGURATION SETTINGS:\n");
    printf("   • Iterations: Define how many times each algorithm is executed to calculate\n");
    printf("                 an accurate average time (mitigates CPU spike anomalies).\n");
    printf("   • Export Format: Save the benchmark results to external report files in CSV,\n");
    printf("                    Markdown, or JSON formats.\n\n");
    printf("BENCHMARK SUITES:\n");
    printf("   1. Sorting Algorithms           8. Hash Map Collision Resolution\n");
    printf("   2. Searching Algorithms         9. Trees Lookup Performance\n");
    printf("   3. Graph Shortest Paths         10. Backtracking Algorithms\n");
    printf("   4. Minimum Spanning Trees (MST) 11. Network Flow Algorithms\n");
    printf("   5. Job Scheduling               12. Advanced Heaps\n");
    printf("   6. String Matching              13. Cache Replacement Simulator\n");
    printf("   7. DP vs Naive Recursion        14. Compression & Encoding\n\n");

    printf("HOW TO RUN UTILITIES IN THIS SUITE:\n");
    printf("   Main Menu ➔ Option 19 (System Utilities & Diagnostics)\n");
    printf("   Main Menu ➔ Option 15 (Benchmarking Suite)\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
