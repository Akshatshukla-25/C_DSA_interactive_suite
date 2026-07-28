#include "count_min_sketch.h"
#include "bloom_filter.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

CountMinSketch* cms_init(double epsilon, double delta)
{
    if (epsilon <= 0.0 || epsilon >= 1.0 || delta <= 0.0 || delta >= 1.0)
    {
        return NULL;
    }

    CountMinSketch* sketch = (CountMinSketch*)malloc(sizeof(CountMinSketch));
    if (!sketch)
    {
        return NULL;
    }

    size_t w = (size_t)ceil(M_E / epsilon);
    size_t d = (size_t)ceil(log(1.0 / delta));

    if (w < 16)
    {
        w = 16;
    }
    if (d < 1)
    {
        d = 1;
    }

    sketch->table = (uint32_t**)malloc(sizeof(uint32_t*) * d);
    if (!sketch->table)
    {
        free(sketch);
        return NULL;
    }

    for (size_t i = 0; i < d; i++)
    {
        sketch->table[i] = (uint32_t*)calloc(w, sizeof(uint32_t));
        if (!sketch->table[i])
        {
            for (size_t j = 0; j < i; j++)
            {
                free(sketch->table[j]);
            }
            free(sketch->table);
            free(sketch);
            return NULL;
        }
    }

    sketch->width = w;
    sketch->depth = d;
    sketch->total_count = 0;
    sketch->epsilon = epsilon;
    sketch->delta = delta;

    return sketch;
}

bool cms_add(CountMinSketch* sketch, const void* data, size_t len, uint32_t count)
{
    if (!sketch || !sketch->table || !data || len == 0 || count == 0)
    {
        return false;
    }

    uint64_t h1 = bloom_fnv1a_hash(data, len, 0x13579ACE);
    uint64_t h2 = bloom_fnv1a_hash(data, len, h1 ^ 0x2468BDF0);

    for (size_t i = 0; i < sketch->depth; i++)
    {
        uint64_t combined = h1 + i * h2;
        size_t col = combined % sketch->width;
        sketch->table[i][col] += count;
    }

    sketch->total_count += count;
    return true;
}

uint32_t cms_estimate(const CountMinSketch* sketch, const void* data, size_t len)
{
    if (!sketch || !sketch->table || !data || len == 0)
    {
        return 0;
    }

    uint64_t h1 = bloom_fnv1a_hash(data, len, 0x13579ACE);
    uint64_t h2 = bloom_fnv1a_hash(data, len, h1 ^ 0x2468BDF0);

    uint32_t min_freq = UINT32_MAX;

    for (size_t i = 0; i < sketch->depth; i++)
    {
        uint64_t combined = h1 + i * h2;
        size_t col = combined % sketch->width;
        if (sketch->table[i][col] < min_freq)
        {
            min_freq = sketch->table[i][col];
        }
    }

    return min_freq;
}

void cms_free(CountMinSketch* sketch)
{
    if (!sketch)
    {
        return;
    }
    if (sketch->table)
    {
        for (size_t i = 0; i < sketch->depth; i++)
        {
            if (sketch->table[i])
            {
                free(sketch->table[i]);
            }
        }
        free(sketch->table);
    }
    free(sketch);
}
