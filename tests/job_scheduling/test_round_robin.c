#define TEST_MOCK_SCHEDULING
#include "../../src/job_scheduling/job_scheduling.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/job_scheduling/round_robin.c"

void test_round_robin_basic()
{
    Process procs[3] = {
        {.id = 1, .arrival = 0, .burst = 4, .remaining = 4},
        {.id = 2, .arrival = 1, .burst = 5, .remaining = 5},
        {.id = 3, .arrival = 2, .burst = 2, .remaining = 2},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    round_robin_schedule(procs, 3, 2, segments, &segment_count);

    // Find and verify each process's computed values
    for (int i = 0; i < 3; i++)
    {
        if (procs[i].id == 1)
        {
            assert(procs[i].completion == 8);
            assert(procs[i].turnaround == 8);
            assert(procs[i].waiting == 4);
        }
        else if (procs[i].id == 2)
        {
            assert(procs[i].completion == 11);
            assert(procs[i].turnaround == 10);
            assert(procs[i].waiting == 5);
        }
        else if (procs[i].id == 3)
        {
            assert(procs[i].completion == 6);
            assert(procs[i].turnaround == 4);
            assert(procs[i].waiting == 2);
        }
    }
    printf("Round Robin basic test passed\n");
}

int main()
{
    test_round_robin_basic();
    printf("All Round Robin tests passed\n");
    return 0;
}
