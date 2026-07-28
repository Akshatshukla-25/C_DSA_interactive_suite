#define TEST_MOCK_SCHEDULING
#include "../../src/job_scheduling/job_scheduling.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/job_scheduling/srtf.c"

void test_srtf_basic()
{
    Process procs[4] = {
        {.id = 1, .arrival = 0, .burst = 8, .remaining = 8},
        {.id = 2, .arrival = 1, .burst = 4, .remaining = 4},
        {.id = 3, .arrival = 2, .burst = 9, .remaining = 9},
        {.id = 4, .arrival = 3, .burst = 5, .remaining = 5},
    };

    GanttSegment segments[JS_MAX_SEGMENTS];
    int segment_count = 0;

    srtf_schedule(procs, 4, segments, &segment_count);

    // Find and verify each process's computed values
    for (int i = 0; i < 4; i++)
    {
        if (procs[i].id == 1)
        {
            assert(procs[i].completion == 17);
            assert(procs[i].turnaround == 17);
            assert(procs[i].waiting == 9);
        }
        else if (procs[i].id == 2)
        {
            assert(procs[i].completion == 5);
            assert(procs[i].turnaround == 4);
            assert(procs[i].waiting == 0);
        }
        else if (procs[i].id == 3)
        {
            assert(procs[i].completion == 26);
            assert(procs[i].turnaround == 24);
            assert(procs[i].waiting == 15);
        }
        else if (procs[i].id == 4)
        {
            assert(procs[i].completion == 10);
            assert(procs[i].turnaround == 7);
            assert(procs[i].waiting == 2);
        }
    }
    printf("SRTF basic test passed\n");
}

int main()
{
    test_srtf_basic();
    printf("All SRTF tests passed\n");
    return 0;
}
