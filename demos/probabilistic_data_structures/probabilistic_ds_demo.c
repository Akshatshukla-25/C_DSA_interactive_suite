#include "bloom_filter.h"
#include "count_min_sketch.h"
#include "hyperloglog.h"
#include "safe_input.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void run_bloom_filter_demo(void)
{
    printf("\n----------------------------------------------------\n");
    printf("        INTERACTIVE BLOOM FILTER DEMO               \n");
    printf("----------------------------------------------------\n");

    BloomFilter* filter = bloom_init(100, 0.01);
    if (!filter)
    {
        printf("Failed to initialize Bloom Filter.\n");
        return;
    }

    printf("[INITIALIZED] Bit Array Size: %zu bits (%zu bytes), Hash Functions: %zu\n",
           filter->bit_size, (filter->bit_size + 7) / 8, filter->num_hashes);

    const char* sample_items[] = {"user_alice", "user_bob", "user_charlie", "user_david"};
    for (size_t i = 0; i < 4; i++)
    {
        bloom_add(filter, sample_items[i], strlen(sample_items[i]));
        printf(" -> Inserted '%s'\n", sample_items[i]);
    }

    printf("\nTesting Set Membership Queries:\n");
    printf(" 'user_alice'   : %s\n", bloom_check(filter, "user_alice", strlen("user_alice"))
                                         ? "MAY BE PRESENT"
                                         : "DEFINITELY ABSENT");
    printf(" 'user_charlie' : %s\n", bloom_check(filter, "user_charlie", strlen("user_charlie"))
                                         ? "MAY BE PRESENT"
                                         : "DEFINITELY ABSENT");
    printf(" 'user_eve'     : %s\n", bloom_check(filter, "user_eve", strlen("user_eve"))
                                         ? "MAY BE PRESENT"
                                         : "DEFINITELY ABSENT");

    bloom_free(filter);
    printf("----------------------------------------------------\n");
}

static void run_count_min_sketch_demo(void)
{
    printf("\n----------------------------------------------------\n");
    printf("     INTERACTIVE COUNT-MIN SKETCH STREAM DEMO       \n");
    printf("----------------------------------------------------\n");

    CountMinSketch* sketch = cms_init(0.001, 0.01);
    if (!sketch)
    {
        printf("Failed to initialize Count-Min Sketch.\n");
        return;
    }

    printf("[INITIALIZED] Matrix Dimensions: %zu Width x %zu Depth\n", sketch->width,
           sketch->depth);

    printf("Simulating data stream insertion...\n");
    cms_add(sketch, "HTTP_GET_/api/v1/user", strlen("HTTP_GET_/api/v1/user"), 500);
    cms_add(sketch, "HTTP_POST_/api/v1/login", strlen("HTTP_POST_/api/v1/login"), 250);
    cms_add(sketch, "HTTP_GET_/api/v1/items", strlen("HTTP_GET_/api/v1/items"), 120);

    printf("\nFrequency Estimates:\n");
    printf(" 'HTTP_GET_/api/v1/user'  (Actual: 500) -> Estimated: %u\n",
           cms_estimate(sketch, "HTTP_GET_/api/v1/user", strlen("HTTP_GET_/api/v1/user")));
    printf(" 'HTTP_POST_/api/v1/login' (Actual: 250) -> Estimated: %u\n",
           cms_estimate(sketch, "HTTP_POST_/api/v1/login", strlen("HTTP_POST_/api/v1/login")));
    printf(" 'HTTP_DELETE_/admin'     (Actual:   0) -> Estimated: %u\n",
           cms_estimate(sketch, "HTTP_DELETE_/admin", strlen("HTTP_DELETE_/admin")));

    cms_free(sketch);
    printf("----------------------------------------------------\n");
}

static void run_hyperloglog_demo(void)
{
    printf("\n----------------------------------------------------\n");
    printf("      INTERACTIVE HYPERLOGLOG CARDINALITY DEMO      \n");
    printf("----------------------------------------------------\n");

    uint8_t precision = 12;
    HyperLogLog* hll = hll_init(precision);
    if (!hll)
    {
        printf("Failed to initialize HyperLogLog.\n");
        return;
    }

    printf("[INITIALIZED] Registers: %zu (2^%d), Memory: %zu bytes\n", hll->m, precision, hll->m);

    size_t unique_count = 2500;
    printf("Inserting %zu distinct elements into HyperLogLog stream...\n", unique_count);
    char buf[64];
    for (size_t i = 0; i < unique_count; i++)
    {
        snprintf(buf, sizeof(buf), "unique_stream_item_%zu", i);
        hll_add(hll, buf, strlen(buf));
    }

    uint64_t est = hll_count(hll);
    double error_pct = (fabs((double)est - (double)unique_count) / (double)unique_count) * 100.0;

    printf("\nResults:\n");
    printf(" Actual Unique Count      : %zu\n", unique_count);
    printf(" HLL Estimated Count     : %llu\n", (unsigned long long)est);
    printf(" Relative Estimation Error: %.2f%%\n", error_pct);

    hll_free(hll);
    printf("----------------------------------------------------\n");
}

void probabilistic_ds_demo(void)
{
    while (1)
    {
        printf("\n========================================================\n");
        printf("        PROBABILISTIC DATA STRUCTURES MODULE            \n");
        printf("========================================================\n");
        printf("1. Bloom Filter (Space-Efficient Set Membership)\n");
        printf("2. Count-Min Sketch (Sub-linear Frequency Estimation)\n");
        printf("3. HyperLogLog (Logarithmic Memory Cardinality Estimator)\n");
        printf("-1. Return to Main Menu\n");

        int choice;
        int status = safe_input_int(&choice, "\nEnter choice: ", 1, 3);

        if (status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting Probabilistic Data Structures Module...\n");
            return;
        }

        if (status == 0)
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                run_bloom_filter_demo();
                break;
            case 2:
                run_count_min_sketch_demo();
                break;
            case 3:
                run_hyperloglog_demo();
                break;
        }
    }
}
