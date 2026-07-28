#include "job_scheduling.h"
#include <stdio.h>
#include <time.h>

// Shortest Job First, non-preemptive: at each step pick the shortest-burst job
// among those that have already arrived; once started it runs to completion.
// note: the time measured by clock() covers the scheduling computation only and
// is for demonstration only, not a measure of the algorithm's efficiency.

void sjf_schedule(Process* procs, int n, GanttSegment* segments, int* segment_count)
{
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

            if (chosen == -1 || procs[i].burst < procs[chosen].burst ||
                (procs[i].burst == procs[chosen].burst && procs[i].arrival < procs[chosen].arrival))
            {
                chosen = i;
            }
        }

        if (chosen == -1)
        {
            // no job has arrived yet, idle one tick and try again
            js_add_segment(segments, segment_count, -1, current_time);
            current_time++;
            continue;
        }

        for (int t = 0; t < procs[chosen].burst; t++)
        {
            js_add_segment(segments, segment_count, procs[chosen].id, current_time);
            current_time++;
        }

        procs[chosen].completion = current_time;
        procs[chosen].turnaround = procs[chosen].completion - procs[chosen].arrival;
        procs[chosen].waiting = procs[chosen].turnaround - procs[chosen].burst;
        done[chosen] = 1;
        completed++;
    }
}
