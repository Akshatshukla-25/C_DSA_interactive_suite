#define TEST_MOCK_SCHEDULING
#include "../../src/job_scheduling/job_scheduling.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/job_scheduling/priority_scheduling.c"

void test_priority_scheduling_basic()
{
    Process procs[3] = {
        {.id = 1, .arrival = 0, .burst = 4, .remaining = 4, .priority = 3},
        {.id = 2, .arrival = 1, .burst = 5, .remaining = 5, .priority = 1},
        {.id = 3, .arrival = 2, .burst = 2, .remaining = 2, .priority = 2},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    priority_scheduling(procs, 3, segments, &segment_count);

    for (int i = 0; i < 3; i++)
    {
        if (procs[i].id == 1)
        {
            assert(procs[i].completion == 4);
            assert(procs[i].turnaround == 4);
            assert(procs[i].waiting == 0);
        }
        else if (procs[i].id == 2)
        {
            assert(procs[i].completion == 9);
            assert(procs[i].turnaround == 8);
            assert(procs[i].waiting == 3);
        }
        else if (procs[i].id == 3)
        {
            assert(procs[i].completion == 11);
            assert(procs[i].turnaround == 9);
            assert(procs[i].waiting == 7);
        }
    }
    printf("Priority non-preemptive scheduling basic test passed\n");
}

int main()
{
    test_priority_scheduling_basic();
    printf("All Priority scheduling tests passed\n");
    return 0;
}