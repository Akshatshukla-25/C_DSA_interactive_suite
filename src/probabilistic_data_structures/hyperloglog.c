#include "hyperloglog.h"
#include "bloom_filter.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static double get_alpha_m(size_t m)
{
    switch (m)
    {
        case 16:
            return 0.673;
        case 32:
            return 0.697;
        case 64:
            return 0.709;
        default:
            return 0.7213 / (1.0 + 1.079 / (double)m);
    }
}

static uint8_t count_leading_zeros_64(uint64_t val)
{
    if (val == 0)
    {
        return 64;
    }
#if defined(__GNUC__) || defined(__clang__)
    return (uint8_t)__builtin_clzll(val);
#else
    uint8_t count = 0;
    while ((val & (1ULL << 63)) == 0)
    {
        count++;
        val <<= 1;
    }
    return count;
#endif
}

HyperLogLog* hll_init(uint8_t b)
{
    if (b < 4 || b > 16)
    {
        return NULL;
    }

    HyperLogLog* hll = (HyperLogLog*)malloc(sizeof(HyperLogLog));
    if (!hll)
    {
        return NULL;
    }

    size_t m = 1U << b;
    hll->registers = (uint8_t*)calloc(m, sizeof(uint8_t));
    if (!hll->registers)
    {
        free(hll);
        return NULL;
    }

    hll->m = m;
    hll->b = b;
    hll->alpha_m = get_alpha_m(m);

    return hll;
}

bool hll_add(HyperLogLog* hll, const void* data, size_t len)
{
    if (!hll || !hll->registers || !data || len == 0)
    {
        return false;
    }

    uint64_t hash = bloom_fnv1a_hash(data, len, 0x9876543210FEDCBAULL);

    size_t idx = (size_t)(hash & (hll->m - 1));
    uint64_t w = hash >> hll->b;

    uint8_t rho;
    if (w == 0)
    {
        rho = (uint8_t)(64 - hll->b + 1);
    }
    else
    {
        rho = (uint8_t)(count_leading_zeros_64(w) - hll->b + 1);
    }

    if (rho > hll->registers[idx])
    {
        hll->registers[idx] = rho;
    }

    return true;
}

uint64_t hll_count(const HyperLogLog* hll)
{
    if (!hll || !hll->registers)
    {
        return 0;
    }

    double sum = 0.0;
    size_t zero_registers = 0;

    for (size_t i = 0; i < hll->m; i++)
    {
        uint8_t val = hll->registers[i];
        sum += 1.0 / (double)(1ULL << val);
        if (val == 0)
        {
            zero_registers++;
        }
    }

    double estimate = hll->alpha_m * (double)hll->m * (double)hll->m / sum;

    /* Linear counting for small ranges */
    if (estimate <= 2.5 * (double)hll->m)
    {
        if (zero_registers > 0)
        {
            estimate = (double)hll->m * log((double)hll->m / (double)zero_registers);
        }
    }
    else
    {
        double pow2_32 = 4294967296.0;
        if (estimate > (1.0 / 30.0) * pow2_32)
        {
            estimate = -pow2_32 * log(1.0 - (estimate / pow2_32));
        }
    }

    return (uint64_t)round(estimate);
}

void hll_free(HyperLogLog* hll)
{
    if (!hll)
    {
        return;
    }
    if (hll->registers)
    {
        free(hll->registers);
    }
    free(hll);
}
