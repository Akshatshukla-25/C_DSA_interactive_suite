#define TEST_MOCK_SCHEDULING
#include "../../src/job_scheduling/job_scheduling.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/job_scheduling/sjf.c"

void test_sjf_basic()
{
    Process procs[4] = {
        {.id = 1, .arrival = 0, .burst = 6, .remaining = 6},
        {.id = 2, .arrival = 2, .burst = 2, .remaining = 2},
        {.id = 3, .arrival = 4, .burst = 1, .remaining = 1},
        {.id = 4, .arrival = 5, .burst = 4, .remaining = 4},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    sjf_schedule(procs, 4, segments, &segment_count);

    // Find and verify each process's computed values
    for (int i = 0; i < 4; i++)
    {
        if (procs[i].id == 1)
        {
            assert(procs[i].completion == 6);
            assert(procs[i].turnaround == 6);
            assert(procs[i].waiting == 0);
        }
        else if (procs[i].id == 2)
        {
            assert(procs[i].completion == 9);
            assert(procs[i].turnaround == 7);
            assert(procs[i].waiting == 5);
        }
        else if (procs[i].id == 3)
        {
            assert(procs[i].completion == 7);
            assert(procs[i].turnaround == 3);
            assert(procs[i].waiting == 2);
        }
        else if (procs[i].id == 4)
        {
            assert(procs[i].completion == 13);
            assert(procs[i].turnaround == 8);
            assert(procs[i].waiting == 4);
        }
    }
    printf("SJF basic test passed\n");
}

int main()
{
    test_sjf_basic();
    printf("All SJF tests passed\n");
    return 0;
}
