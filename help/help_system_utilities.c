#include "clear_screen.h"
#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

static void display_telemetry_help(void)
{
    clear_screen();
    display_header("MANUAL: Telemetry & Memory Profiler Engine");
    printf(
        "\n"
        "================================================================================\n"
        " 1. SORTING TELEMETRY DASHBOARD\n"
        "================================================================================\n"
        " Concept:\n"
        "   Tracks real-time algorithmic operations, comparisons, swaps, and execution timers.\n"
        "   - Features: Real-time swap counters, time-series metrics, comparative dashboards.\n\n"
        "================================================================================\n"
        " 2. MEMORY INSPECTOR & PROFILER\n"
        "================================================================================\n"
        " Concept:\n"
        "   Intercepts malloc/free allocations to audit heap usage and detect memory leaks.\n"
        "   - Features: Active allocation tracking, byte leakage alerts, pointer inspection.\n\n"
        " Press [ENTER] to return to System Utilities Help Menu...");
    getchar();
}

static void display_serialization_help(void)
{
    clear_screen();
    display_header("MANUAL: State Serialization & Persistence Engine");
    printf(
        "\n"
        "================================================================================\n"
        " STATE SERIALIZATION & DESERIALIZATION\n"
        "================================================================================\n"
        " Concept:\n"
        "   Serializes live in-memory data structures (BST, AVL Trees, Graphs) to binary payload\n"
        "   files on disk and restores exact state during application execution.\n"
        "   - Supported Structures: Binary Search Trees, AVL Trees, Weighted Graphs.\n"
        "   - Data Integrity: Checksum-verified binary payloads.\n\n"
        " Press [ENTER] to return to System Utilities Help Menu...");
    getchar();
}

void help_system_utilities_menu(void)
{
    while (1)
    {
        clear_screen();
        display_header("Help: System Utilities, Telemetry & Serialization");

        int choice;
        int status = safe_input_int(&choice,
                                    "\nSystem Utilities Topics:\n"
                                    "------------------------\n"
                                    "1. Sorting Telemetry & Memory Profiler Engine\n"
                                    "2. State Serialization & Binary Disk Persistence\n"
                                    "\nenter choice ('-1' to return): ",
                                    1, 2);

        if (status == INPUT_EXIT_SIGNAL)
        {
            return;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                display_telemetry_help();
                break;
            case 2:
                display_serialization_help();
                break;
        }
    }
}
