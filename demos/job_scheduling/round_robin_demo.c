#include "job_scheduling.h"
#include "safe_input.h"
#include <stdio.h>
#include <time.h>

void round_robin_demo(void)
{
    Process procs[10];
    int n;

    if (!js_read_processes(procs, &n, 0))
    {
        printf("\nExiting round robin demo....\n");
        return;
    }

    int quantum;

    while (1)
    {
        int quantum_status =
            safe_input_int(&quantum, "\nenter the time quantum (1 to 1000): ", 1, 1000);

        if (quantum_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting round robin demo....\n");
            return;
        }
        if (quantum_status == 0)
        {
            continue;
        }
        break;
    }

    clock_t start_t, end_t;
    double total_t;

    start_t = clock();

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    round_robin_schedule(procs, n, quantum, segments, &segment_count);

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    js_print_result(procs, n);
    js_print_gantt(segments, segment_count);
    printf("\ntotal CPU time taken for round robin scheduling:- %f seconds\n", total_t);
}
