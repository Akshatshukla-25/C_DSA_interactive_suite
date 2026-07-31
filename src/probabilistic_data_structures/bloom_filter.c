#include "bloom_filter.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNV_64_PRIME 0x100000001b3ULL
#define FNV_64_OFFSET 0xcbf29ce484222325ULL

uint64_t bloom_fnv1a_hash(const void* data, size_t len, uint64_t seed)
{
    if (!data)
    {
        return 0;
    }
    const uint8_t* ptr = (const uint8_t*)data;
    uint64_t hash = FNV_64_OFFSET ^ seed;
    for (size_t i = 0; i < len; i++)
    {
        hash ^= ptr[i];
        hash *= FNV_64_PRIME;
    }
    return hash;
}

BloomFilter* bloom_init(size_t expected_items, double false_positive_rate)
{
    if (expected_items == 0 || false_positive_rate <= 0.0 || false_positive_rate >= 1.0)
    {
        return NULL;
    }

    BloomFilter* filter = (BloomFilter*)malloc(sizeof(BloomFilter));
    if (!filter)
    {
        return NULL;
    }

    /* Optimal bit size m = - (n * ln(p)) / (ln(2)^2) */
    double ln2 = log(2.0);
    double num_bits = -((double)expected_items * log(false_positive_rate)) / (ln2 * ln2);
    size_t m = (size_t)ceil(num_bits);
    if (m < 64)
    {
        m = 64;
    }

    /* Optimal hash count k = (m / n) * ln(2) */
    size_t k = (size_t)round(((double)m / (double)expected_items) * ln2);
    if (k < 1)
    {
        k = 1;
    }

    /* Guard against size_t wrap: (m + 7) overflows when m > SIZE_MAX - 7 */
    if (m > SIZE_MAX - 7)
    {
        free(filter);
        return NULL;
    }
    size_t byte_size = (m + 7) / 8;
    filter->bit_array = (uint8_t*)calloc(byte_size, sizeof(uint8_t));
    if (!filter->bit_array)
    {
        free(filter);
        return NULL;
    }

    filter->bit_size = m;
    filter->num_hashes = k;
    filter->count = 0;
    filter->expected_items = expected_items;
    filter->target_fp_rate = false_positive_rate;

    return filter;
}

bool bloom_add(BloomFilter* filter, const void* data, size_t len)
{
    if (!filter || !filter->bit_array || !data || len == 0)
    {
        return false;
    }

    uint64_t h1 = bloom_fnv1a_hash(data, len, 0);
    uint64_t h2 = bloom_fnv1a_hash(data, len, h1);

    for (size_t i = 0; i < filter->num_hashes; i++)
    {
        uint64_t combined = h1 + i * h2;
        size_t bit_index = combined % filter->bit_size;
        filter->bit_array[bit_index / 8] |= (1U << (bit_index % 8));
    }

    filter->count++;
    return true;
}

bool bloom_check(const BloomFilter* filter, const void* data, size_t len)
{
    if (!filter || !filter->bit_array || !data || len == 0)
    {
        return false;
    }

    uint64_t h1 = bloom_fnv1a_hash(data, len, 0);
    uint64_t h2 = bloom_fnv1a_hash(data, len, h1);

    for (size_t i = 0; i < filter->num_hashes; i++)
    {
        uint64_t combined = h1 + i * h2;
        size_t bit_index = combined % filter->bit_size;
        if (!(filter->bit_array[bit_index / 8] & (1U << (bit_index % 8))))
        {
            return false;
        }
    }

    return true;
}

void bloom_free(BloomFilter* filter)
{
    if (!filter)
    {
        return;
    }
    if (filter->bit_array)
    {
        free(filter->bit_array);
    }
    free(filter);
}
