#include "cache.h"
#include <limits.h>
#include <stdio.h>

bool cache_access_opt(Cache* cache, int page_id, const int* ref_str, int ref_len, int current_idx,
                      bool is_write)
{
    cache_normalize_access_counter(cache);
    cache->access_counter++;

    // Search for page in the cache (Hit check)
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid && cache->blocks[i].page_id == page_id)
        {
            cache->hits++;
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

    // If cache is not full, insert in first invalid slot
    if (cache->size < cache->capacity)
    {
        for (int i = 0; i < cache->capacity; i++)
        {
            if (!cache->blocks[i].is_valid)
            {
                cache->blocks[i].page_id = page_id;
                cache->blocks[i].is_valid = true;
                cache->blocks[i].is_dirty = is_write;
                cache->blocks[i].last_access_time = cache->access_counter;
                cache->last_accessed_slot = i;
                cache->size++;
                return false; // Miss (without eviction)
            }
        }
    }

    // Cache is full: Find block whose next access is furthest in future
    int evict_idx = 0;
    int max_next_access = -1;

    for (int i = 0; i < cache->capacity; i++)
    {
        int page = cache->blocks[i].page_id;
        int next_access = INT_MAX; // Infinity if never accessed again

        for (int j = current_idx + 1; j < ref_len; j++)
        {
            if (ref_str[j] == page)
            {
                next_access = j;
                break;
            }
        }

        if (next_access > max_next_access)
        {
            max_next_access = next_access;
            evict_idx = i;
        }
        else if (next_access == max_next_access)
        {
            // Tie-break with LRU
            if (cache->blocks[i].last_access_time < cache->blocks[evict_idx].last_access_time)
            {
                evict_idx = i;
            }
        }
    }

    // Perform eviction
    cache->blocks[evict_idx].page_id = page_id;
    cache->blocks[evict_idx].is_valid = true;
    cache->blocks[evict_idx].is_dirty = is_write;
    cache->blocks[evict_idx].last_access_time = cache->access_counter;
    cache->last_accessed_slot = evict_idx;

    return false; // Miss (with eviction)
}
