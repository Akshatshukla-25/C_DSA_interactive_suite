#include "display_header.h"
#include "hyperloglog.h"
#include "safe_input.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hyperloglog_demo(void)
{
    display_header("HyperLogLog (Cardinality Estimator)");

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
}
