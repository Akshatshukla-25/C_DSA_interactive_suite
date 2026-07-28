#include "job_scheduling.h"
#include <stdio.h>
#include <time.h>

void srtf_demo(void)
{
    Process procs[10];
    int n;

    if (!js_read_processes(procs, &n, 0))
    {
        printf("\nExiting SRTF demo....\n");
        return;
    }

    clock_t start_t, end_t;
    double total_t;

    start_t = clock();

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;
    
    srtf_schedule(procs, n, segments, &segment_count);
    
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    js_print_result(procs, n);
    js_print_gantt(segments, segment_count);
    printf("\ntotal CPU time taken for SRTF scheduling:- %f seconds\n", total_t);
}
