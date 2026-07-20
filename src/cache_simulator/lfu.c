#include "cache.h"
#include <stdio.h>

bool cache_access_lfu(Cache* cache, int page_id, bool is_write)
{
    cache_normalize_access_counter(cache);
    cache->access_counter++;

    // Periodic Frequency Aging / Decay (every 8 accesses)
    if (cache->access_counter > 0 && cache->access_counter % 8 == 0)
    {
        for (int i = 0; i < cache->capacity; i++)
        {
            if (cache->blocks[i].is_valid)
            {
                cache->blocks[i].frequency /= 2;
            }
        }
    }

    // Search for page in the cache (Hit check)
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid && cache->blocks[i].page_id == page_id)
        {
            cache->hits++;
            if (cache->blocks[i].frequency < 2000000000)
            {
                cache->blocks[i].frequency++;
            }
            cache->blocks[i].last_access_time = cache->access_counter;
            cache->last_accessed_slot = i;
            if (is_write)
            {
                cache->blocks[i].is_dirty = true;
            }
            return true; // Hit
        }
    }

    // Cache Miss
    cache->misses++;

    // If cache is not full, insert in the first invalid slot
    if (cache->size < cache->capacity)
    {
        for (int i = 0; i < cache->capacity; i++)
        {
            if (!cache->blocks[i].is_valid)
            {
                cache->blocks[i].page_id = page_id;
                cache->blocks[i].is_valid = true;
                cache->blocks[i].is_dirty = is_write;
                cache->blocks[i].frequency = 1;
                cache->blocks[i].last_access_time = cache->access_counter;
                cache->last_accessed_slot = i;
                cache->size++;
                return false; // Miss (inserted without eviction)
            }
        }
    }

    // Cache is full: Find block with MINIMUM frequency.
    // Break ties using LRU (smallest last_access_time)
    int evict_idx = 0;
    int min_freq = cache->blocks[0].frequency;
    int min_access = cache->blocks[0].last_access_time;

    for (int i = 1; i < cache->capacity; i++)
    {
        if (cache->blocks[i].frequency < min_freq)
        {
            min_freq = cache->blocks[i].frequency;
            min_access = cache->blocks[i].last_access_time;
            evict_idx = i;
        }
        else if (cache->blocks[i].frequency == min_freq)
        {
            // Tie-break with LRU
            if (cache->blocks[i].last_access_time < min_access)
            {
                min_access = cache->blocks[i].last_access_time;
                evict_idx = i;
            }
        }
    }

    // Perform eviction
    cache->blocks[evict_idx].page_id = page_id;
    cache->blocks[evict_idx].is_valid = true;
    cache->blocks[evict_idx].is_dirty = is_write;
    cache->blocks[evict_idx].frequency = 1;
    cache->blocks[evict_idx].last_access_time = cache->access_counter;
    cache->last_accessed_slot = evict_idx;

    return false; // Miss (with eviction)
}
