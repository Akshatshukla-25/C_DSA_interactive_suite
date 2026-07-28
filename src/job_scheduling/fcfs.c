#include "job_scheduling.h"
#include <stdio.h>
#include <time.h>

// First-Come-First-Served: run the processes in arrival order (ties broken by
// the order they were entered). The CPU idles forward to the next arrival if it
// would otherwise be free.
// note: the time measured by clock() covers the scheduling computation only (it
// starts after the process list is read and stops before the results are
// printed). it is for demonstration only and must not be treated as a measure
// of the algorithm's efficiency.

void fcfs_schedule(Process *procs, int n, GanttSegment *segments, int *segment_count)
{
    // Stable insertion sort to keep input order on ties
    for (int i = 1; i < n; i++)
    {
        Process key = procs[i];
        int j = i - 1;
        while (j >= 0 && procs[j].arrival > key.arrival)
        {
            procs[j + 1] = procs[j];
            j = j - 1;
        }
        procs[j + 1] = key;
    }

    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        // idle until this process arrives
        while (current_time < procs[i].arrival)
        {
            js_add_segment(segments, segment_count, -1, current_time);
            current_time++;
        }

        for (int t = 0; t < procs[i].burst; t++)
        {
            js_add_segment(segments, segment_count, procs[i].id, current_time);
            current_time++;
        }

        procs[i].completion = current_time;
        procs[i].turnaround = procs[i].completion - procs[i].arrival;
        procs[i].waiting = procs[i].turnaround - procs[i].burst;
    }
}
