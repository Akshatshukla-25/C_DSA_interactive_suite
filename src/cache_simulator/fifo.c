#include "cache.h"
#include <stdio.h>

bool cache_access_fifo(Cache* cache, int page_id, bool is_write)
{
    // Search for page in the cache (Hit check)
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid && cache->blocks[i].page_id == page_id)
        {
            cache->hits++;
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
                cache->last_accessed_slot = i;
                cache->size++;
                return false; // Miss (inserted without eviction)
            }
        }
    }

    // Cache is full: Evict using FIFO policy
    int evict_idx = cache->fifo_index;

    // Perform eviction
    cache->blocks[evict_idx].page_id = page_id;
    cache->blocks[evict_idx].is_valid = true;
    cache->blocks[evict_idx].is_dirty = is_write;
    cache->last_accessed_slot = evict_idx;

    // Update FIFO pointer (circular queue)
    cache->fifo_index = (cache->fifo_index + 1) % cache->capacity;

    return false; // Miss (with eviction)
}
