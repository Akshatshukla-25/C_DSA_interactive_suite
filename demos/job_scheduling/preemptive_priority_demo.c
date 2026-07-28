#include "job_scheduling.h"
#include <stdio.h>
#include <time.h>

void preemptive_priority_demo(void)
{
    Process procs[10];
    int n;

    if (!js_read_processes(procs, &n, 1))
    {
        printf("\nExiting preemptive priority demo....\n");
        return;
    }

    clock_t start_t, end_t;
    double total_t;

    start_t = clock();

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;
    
    preemptive_priority_schedule(procs, n, segments, &segment_count);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    js_print_result(procs, n);
    js_print_gantt(segments, segment_count);
    printf("\ntotal CPU time taken for preemptive priority scheduling:- %f seconds\n", total_t);
}
