#define TEST_MOCK_SCHEDULING
#include "../../src/job_scheduling/job_scheduling.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/job_scheduling/fcfs.c"

void test_fcfs_basic(void)
{
    Process procs[3] = {
        {.id = 1, .arrival = 0, .burst = 5, .remaining = 5},
        {.id = 2, .arrival = 2, .burst = 3, .remaining = 3},
        {.id = 3, .arrival = 4, .burst = 1, .remaining = 1},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    fcfs_schedule(procs, 3, segments, &segment_count);

    assert(procs[0].completion == 5);
    assert(procs[0].turnaround == 5);
    assert(procs[0].waiting == 0);

    assert(procs[1].completion == 8);
    assert(procs[1].turnaround == 6);
    assert(procs[1].waiting == 3);

    assert(procs[2].completion == 9);
    assert(procs[2].turnaround == 5);
    assert(procs[2].waiting == 4);

    printf("FCFS basic test passed\n");
}

void test_fcfs_zero_burst(void)
{
    Process procs[1] = {
        {.id = 1, .arrival = 0, .burst = 0, .remaining = 0},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    fcfs_schedule(procs, 1, segments, &segment_count);

    assert(procs[0].completion == 0);
    assert(procs[0].turnaround == 0);
    assert(procs[0].waiting == 0);

    printf("FCFS zero burst test passed\n");
}

int main()
{
    test_fcfs_basic();
    test_fcfs_zero_burst();
    printf("All FCFS tests passed\n");
    return 0;
}
