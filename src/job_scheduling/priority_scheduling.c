#include "job_scheduling.h"
#include <stdio.h>

// Priority scheduling, non-preemptive: among the jobs that have arrived, run
// the one with the highest priority (lowest priority number) to completion.
// Ties are broken by earlier arrival.
void priority_scheduling_demo(void)
{
    Process procs[10];
    int n;

    if (!js_read_processes(procs, &n, 1))
    {
        printf("\nExiting priority scheduling demo....\n");
        return;
    }

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;
    int done[10] = {0};
    int completed = 0;
    int current_time = 0;

    while (completed < n)
    {
        int chosen = -1;

        for (int i = 0; i < n; i++)
        {
            if (done[i] || procs[i].arrival > current_time)
            {
                continue;
            }

            if (chosen == -1 || procs[i].priority < procs[chosen].priority ||
                (procs[i].priority == procs[chosen].priority &&
                 procs[i].arrival < procs[chosen].arrival))
            {
                chosen = i;
            }
        }

        if (chosen == -1)
        {
            // no job has arrived yet, idle one tick and try again
            js_add_segment(segments, &segment_count, -1, current_time);
            current_time++;
            continue;
        }

        for (int t = 0; t < procs[chosen].burst; t++)
        {
            js_add_segment(segments, &segment_count, procs[chosen].id, current_time);
            current_time++;
        }

        procs[chosen].completion = current_time;
        procs[chosen].turnaround = procs[chosen].completion - procs[chosen].arrival;
        procs[chosen].waiting = procs[chosen].turnaround - procs[chosen].burst;
        done[chosen] = 1;
        completed++;
    }

    js_print_result(procs, n);
    js_print_gantt(segments, segment_count);
}
