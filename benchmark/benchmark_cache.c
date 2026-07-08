#include "benchmark.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

void run_cache_benchmark(int n)
{
    printf("\n--- Running Cache Replacement Benchmarks (N = %d accesses) ---\n", n);

    int capacity = 4;
    int num_pages = 15;

    int* random_trace = malloc(sizeof(int) * n);
    int* looping_trace = malloc(sizeof(int) * n);
    int* zipfian_trace = malloc(sizeof(int) * n);

    if (!random_trace || !looping_trace || !zipfian_trace)
    {
        printf("Memory allocation failed for benchmark traces.\n");
        free(random_trace);
        free(looping_trace);
        free(zipfian_trace);
        return;
    }

    // Populate Random trace
    for (int i = 0; i < n; i++)
    {
        random_trace[i] = rand() % num_pages;
    }

    // Populate Looping trace (sequence repeating 0..5)
    for (int i = 0; i < n; i++)
    {
        looping_trace[i] = i % 6;
    }

    // Populate Zipfian trace (80-20 rule)
    for (int i = 0; i < n; i++)
    {
        if ((rand() % 100) < 80)
        {
            int hot_count = num_pages * 20 / 100;
            if (hot_count < 1)
                hot_count = 1;
            zipfian_trace[i] = rand() % hot_count;
        }
        else
        {
            int hot_count = num_pages * 20 / 100;
            if (hot_count < 1)
                hot_count = 1;
            zipfian_trace[i] = hot_count + (rand() % (num_pages - hot_count));
        }
    }

    const char* workloads[] = {"Random", "Looping", "Zipfian"};
    int* traces[] = {random_trace, looping_trace, zipfian_trace};

    for (int w = 0; w < 3; w++)
    {
        printf("\nWorkload Pattern: %s\n", workloads[w]);
        printf("------------------------------------\n");
        printf("Algorithm\tHits\tMisses\tHit Rate\n");

        // FIFO
        Cache cache_fifo;
        cache_init(&cache_fifo, capacity);
        for (int i = 0; i < n; i++)
        {
            cache_access_fifo(&cache_fifo, traces[w][i], false);
        }
        printf("FIFO     \t%d\t%d\t%.2f%%\n", cache_fifo.hits, cache_fifo.misses,
               (double)cache_fifo.hits * 100 / n);

        // LRU
        Cache cache_lru;
        cache_init(&cache_lru, capacity);
        for (int i = 0; i < n; i++)
        {
            cache_access_lru(&cache_lru, traces[w][i], false);
        }
        printf("LRU      \t%d\t%d\t%.2f%%\n", cache_lru.hits, cache_lru.misses,
               (double)cache_lru.hits * 100 / n);

        // MRU
        Cache cache_mru;
        cache_init(&cache_mru, capacity);
        for (int i = 0; i < n; i++)
        {
            cache_access_mru(&cache_mru, traces[w][i], false);
        }
        printf("MRU      \t%d\t%d\t%.2f%%\n", cache_mru.hits, cache_mru.misses,
               (double)cache_mru.hits * 100 / n);

        // LFU
        Cache cache_lfu;
        cache_init(&cache_lfu, capacity);
        for (int i = 0; i < n; i++)
        {
            cache_access_lfu(&cache_lfu, traces[w][i], false);
        }
        printf("LFU      \t%d\t%d\t%.2f%%\n", cache_lfu.hits, cache_lfu.misses,
               (double)cache_lfu.hits * 100 / n);

        // Clock
        Cache cache_clock;
        cache_init(&cache_clock, capacity);
        for (int i = 0; i < n; i++)
        {
            cache_access_clock(&cache_clock, traces[w][i], false);
        }
        printf("Clock    \t%d\t%d\t%.2f%%\n", cache_clock.hits, cache_clock.misses,
               (double)cache_clock.hits * 100 / n);

        // OPT
        Cache cache_opt;
        cache_init(&cache_opt, capacity);
        for (int i = 0; i < n; i++)
        {
            cache_access_opt(&cache_opt, traces[w][i], traces[w], n, i, false);
        }
        printf("OPT      \t%d\t%d\t%.2f%%\n", cache_opt.hits, cache_opt.misses,
               (double)cache_opt.hits * 100 / n);
    }

    free(random_trace);
    free(looping_trace);
    free(zipfian_trace);

    printf("\nPress [ENTER] to continue...");
    getchar();
}
