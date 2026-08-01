#include "clear_screen.h"
#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>
#include <stdlib.h>

void help_job_scheduling_menu(void)
{
    while (1)
    {
        clear_screen();
        display_header("Help: Job Scheduling Algorithms");

        printf("JOB SCHEDULING OVERVIEW:\n");
        printf("    Job scheduling algorithms determine the order in which processes or\n");
        printf("    tasks are executed by a system's CPU. They aim to optimize metrics\n");
        printf("    like throughput, latency, turnaround time, and fairness.\n\n");

        printf("COMMON SCHEDULING ALGORITHMS:\n");
        printf("    • First-Come, First-Served (FCFS): Executes tasks in the exact order\n");
        printf("      they arrive. Simple, but suffers from the Convoy Effect.\n");
        printf("    • Shortest Job Next (SJN / SJF): Selects the waiting process with the\n");
        printf("      smallest execution time. Optimal for average waiting time, but\n");
        printf("      can cause starvation for longer jobs.\n");
        printf("    • Round Robin (RR): Assigns a fixed time quantum per process. Cycles\n");
        printf("      through the queue to ensure fairness and responsiveness.\n");
        printf("    • Priority Scheduling: Executes tasks based on a priority ranking.\n");
        printf("      May require \"aging\" techniques to prevent starvation.\n\n");

        printf("OPERATING SYSTEM APPLICATIONS:\n");
        printf("    • Linux CFS (Completely Fair Scheduler): Uses red-black trees to\n");
        printf("      model the priority queue, ensuring fair CPU distribution.\n");
        printf("    • Real-Time Systems: Hard real-time systems use strict priority and\n");
        printf("      deadline-based algorithms like Earliest Deadline First (EDF).\n\n");

        printf("HOW TO RUN IN THIS SUITE:\n");
        printf("    1. Exit to the main menu and select option 21.\n");
        printf("    2. Observe step-by-step simulations of various schedulers.\n\n");

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
