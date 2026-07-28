#include "job_scheduling.h"
#include <stdio.h>
#include <time.h>

// Priority scheduling, non-preemptive: among the jobs that have arrived, run
// the one with the highest priority (lowest priority number) to completion.
// Ties are broken by earlier arrival.
// note: the time measured by clock() covers the scheduling computation only and
// is for demonstration only, not a measure of the algorithm's efficiency.

void priority_scheduling(Process *procs, int n, GanttSegment *segments, int *segment_count)
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
