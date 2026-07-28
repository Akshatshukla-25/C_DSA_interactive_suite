#include "job_scheduling.h"
#include <stdio.h>
#include <time.h>

// Shortest Remaining Time First (preemptive SJF): at every time unit pick the
// arrived, unfinished job with the smallest remaining time and run it for one
// tick. A newly arrived shorter job therefore preempts the running one. Ties
// are broken by earlier arrival, then input order, so the running job is not
// preempted by an equal-remaining peer.
// note: the time measured by clock() covers the scheduling computation only and
// is for demonstration only, not a measure of the algorithm's efficiency.

void srtf_schedule(Process *procs, int n, GanttSegment *segments, int *segment_count)
{
    int completed = 0;
    int current_time = 0;

    while (completed < n)
    {
        int chosen = -1;

        for (int i = 0; i < n; i++)
        {
            if (procs[i].remaining == 0 || procs[i].arrival > current_time)
            {
                continue;
            }

            if (chosen == -1 || procs[i].remaining < procs[chosen].remaining ||
                (procs[i].remaining == procs[chosen].remaining &&
                 procs[i].arrival < procs[chosen].arrival))
            {
                chosen = i;
            }
        }

        if (chosen == -1)
        {
            // nothing has arrived yet, idle one tick
            js_add_segment(segments, segment_count, -1, current_time);
            current_time++;
            continue;
        }

        js_add_segment(segments, segment_count, procs[chosen].id, current_time);
        procs[chosen].remaining--;
        current_time++;

        if (procs[chosen].remaining == 0)
        {
            procs[chosen].completion = current_time;
            procs[chosen].turnaround = procs[chosen].completion - procs[chosen].arrival;
            procs[chosen].waiting = procs[chosen].turnaround - procs[chosen].burst;
            completed++;
        }
    }
}
