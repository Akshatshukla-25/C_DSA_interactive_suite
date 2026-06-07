#include "job_scheduling.h"
#include <stdio.h>

// First-Come-First-Served: run the processes in arrival order (ties broken by
// the order they were entered). The CPU idles forward to the next arrival if it
// would otherwise be free.
void fcfs_demo(void)
{
    Process procs[10];
    int n;

    if (!js_read_processes(procs, &n, 0))
    {
        printf("\nExiting FCFS demo....\n");
        return;
    }

    // selection-style ordering by arrival time, keeping input order on ties
    for (int i = 0; i < n - 1; i++)
    {
        int earliest = i;

        for (int j = i + 1; j < n; j++)
        {
            if (procs[j].arrival < procs[earliest].arrival)
            {
                earliest = j;
            }
        }

        if (earliest != i)
        {
            Process tmp = procs[i];
            procs[i] = procs[earliest];
            procs[earliest] = tmp;
        }
    }

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        // idle until this process arrives
        while (current_time < procs[i].arrival)
        {
            js_add_segment(segments, &segment_count, -1, current_time);
            current_time++;
        }

        for (int t = 0; t < procs[i].burst; t++)
        {
            js_add_segment(segments, &segment_count, procs[i].id, current_time);
            current_time++;
        }

        procs[i].completion = current_time;
        procs[i].turnaround = procs[i].completion - procs[i].arrival;
        procs[i].waiting = procs[i].turnaround - procs[i].burst;
    }

    js_print_result(procs, n);
    js_print_gantt(segments, segment_count);
}
