#define TEST_MOCK_SCHEDULING
#include "../../src/job_scheduling/job_scheduling.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/job_scheduling/preemptive_priority.c"

void test_preemptive_priority_basic()
{
    Process procs[3] = {
        {.id = 1, .arrival = 0, .burst = 5, .remaining = 5, .priority = 2},
        {.id = 2, .arrival = 1, .burst = 2, .remaining = 2, .priority = 1},
        {.id = 3, .arrival = 2, .burst = 3, .remaining = 3, .priority = 3},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    preemptive_priority_schedule(procs, 3, segments, &segment_count);

    for (int i = 0; i < 3; i++)
    {
        if (procs[i].id == 1)
        {
            assert(procs[i].completion == 7);
            assert(procs[i].turnaround == 7);
            assert(procs[i].waiting == 2);
        }
        else if (procs[i].id == 2)
        {
            assert(procs[i].completion == 3);
            assert(procs[i].turnaround == 2);
            assert(procs[i].waiting == 0);
        }
        else if (procs[i].id == 3)
        {
            assert(procs[i].completion == 10);
            assert(procs[i].turnaround == 8);
            assert(procs[i].waiting == 5);
        }
    }

    printf("Preemptive Priority scheduling basic test passed\n");
}

void test_preemptive_priority_ties_and_idle()
{
    Process procs[2] = {
        {.id = 1, .arrival = 2, .burst = 2, .remaining = 2, .priority = 1},
        {.id = 2, .arrival = 3, .burst = 2, .remaining = 2, .priority = 1},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    preemptive_priority_schedule(procs, 2, segments, &segment_count);

    for (int i = 0; i < 2; i++)
    {
        if (procs[i].id == 1)
        {
            assert(procs[i].completion == 4);
            assert(procs[i].turnaround == 2);
            assert(procs[i].waiting == 0);
        }
        else if (procs[i].id == 2)
        {
            assert(procs[i].completion == 6);
            assert(procs[i].turnaround == 3);
            assert(procs[i].waiting == 1);
        }
    }

    printf("Preemptive Priority scheduling ties and idle test passed\n");
}

int main()
{
    test_preemptive_priority_basic();
    test_preemptive_priority_ties_and_idle();
    printf("All Preemptive Priority scheduling tests passed\n");
    return 0;
}
