#include "cache.h"
#include <stdio.h>

bool cache_access_clock(Cache* cache, int page_id, bool is_write)
{
    cache->access_counter++;

    // Search for page in the cache (Hit check)
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid && cache->blocks[i].page_id == page_id)
        {
            cache->hits++;
            cache->blocks[i].reference_bit = 1;
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
                cache->blocks[i].reference_bit = 1;
                cache->last_accessed_slot = i;
                cache->size++;
                return false; // Miss (without eviction)
            }
        }
    }

    // Cache is full: Run Clock (Second Chance) algorithm
    while (1)
    {
        int hand = cache->fifo_index;
        if (cache->blocks[hand].reference_bit == 1)
        {
            cache->blocks[hand].reference_bit = 0;
            cache->fifo_index = (cache->fifo_index + 1) % cache->capacity;
        }
        else
        {
            // Evict page at hand
            cache->blocks[hand].page_id = page_id;
            cache->blocks[hand].is_valid = true;
            cache->blocks[hand].is_dirty = is_write;
            cache->blocks[hand].reference_bit = 1;
            cache->last_accessed_slot = hand;
            cache->fifo_index = (cache->fifo_index + 1) % cache->capacity;
            break;
        }
    }

    return false; // Miss (with eviction)
}

bool cache_access_enhanced_clock(Cache* cache, int page_id, bool is_write)
{
    cache->access_counter++;

    // Search for page in the cache (Hit check)
    for (int i = 0; i < cache->capacity; i++)
    {
        if (cache->blocks[i].is_valid && cache->blocks[i].page_id == page_id)
        {
            cache->hits++;
            cache->blocks[i].reference_bit = 1;
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
                cache->blocks[i].reference_bit = 1;
                cache->last_accessed_slot = i;
                cache->size++;
                return false; // Miss (without eviction)
            }
        }
    }

    // Cache is full: Run Enhanced Second Chance Clock algorithm
    int start_hand = cache->fifo_index;

    // Step 1: Scan for Class 0 (0, 0)
    for (int step = 0; step < cache->capacity; step++)
    {
        int idx = (start_hand + step) % cache->capacity;
        if (cache->blocks[idx].reference_bit == 0 && !cache->blocks[idx].is_dirty)
        {
            cache->blocks[idx].page_id = page_id;
            cache->blocks[idx].is_valid = true;
            cache->blocks[idx].is_dirty = is_write;
            cache->blocks[idx].reference_bit = 1;
            cache->last_accessed_slot = idx;
            cache->fifo_index = (idx + 1) % cache->capacity;
            return false; // Miss (with eviction)
        }
    }

    // Step 2: Scan for Class 1 (0, 1), modifying reference bit of bypassed pages
    for (int step = 0; step < cache->capacity; step++)
    {
        int idx = (start_hand + step) % cache->capacity;
        if (cache->blocks[idx].reference_bit == 0 && cache->blocks[idx].is_dirty)
        {
            cache->blocks[idx].page_id = page_id;
            cache->blocks[idx].is_valid = true;
            cache->blocks[idx].is_dirty = is_write;
            cache->blocks[idx].reference_bit = 1;
            cache->last_accessed_slot = idx;
            cache->fifo_index = (idx + 1) % cache->capacity;
            return false; // Miss (with eviction)
        }
        else
        {
            cache->blocks[idx].reference_bit = 0;
        }
    }

    // Step 3: If Step 2 failed, repeat Step 1
    for (int step = 0; step < cache->capacity; step++)
    {
        int idx = (start_hand + step) % cache->capacity;
        if (cache->blocks[idx].reference_bit == 0 && !cache->blocks[idx].is_dirty)
        {
            cache->blocks[idx].page_id = page_id;
            cache->blocks[idx].is_valid = true;
            cache->blocks[idx].is_dirty = is_write;
            cache->blocks[idx].reference_bit = 1;
            cache->last_accessed_slot = idx;
            cache->fifo_index = (idx + 1) % cache->capacity;
            return false; // Miss (with eviction)
        }
    }

    // Step 4: If Step 3 failed, repeat Step 2
    for (int step = 0; step < cache->capacity; step++)
    {
        int idx = (start_hand + step) % cache->capacity;
        if (cache->blocks[idx].reference_bit == 0 && cache->blocks[idx].is_dirty)
        {
            cache->blocks[idx].page_id = page_id;
            cache->blocks[idx].is_valid = true;
            cache->blocks[idx].is_dirty = is_write;
            cache->blocks[idx].reference_bit = 1;
            cache->last_accessed_slot = idx;
            cache->fifo_index = (idx + 1) % cache->capacity;
            return false; // Miss (with eviction)
        }
    }

    return false;
}
