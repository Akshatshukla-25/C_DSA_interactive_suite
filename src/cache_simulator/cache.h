#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>

/** Maximum supported frame capacity for the Cache Simulator. */
#define CACHE_MAX_CAPACITY 10

/**
 * @brief Represents an individual cache frame block.
 */
typedef struct
{
    int page_id;          /**< Page identifier stored in the block (-1 if empty). */
    bool is_valid;        /**< True if the block contains valid data. */
    bool is_dirty;        /**< True if the block has unwritten modifications. */
    int reference_bit;    /**< Reference bit used by Clock replacement algorithms. */
    int frequency;        /**< Access frequency counter for LFU replacement. */
    int last_access_time; /**< Timestamp of the last access for LRU/MRU. */
} CacheBlock;

/**
 * @brief Main Cache Simulator data structure.
 */
typedef struct
{
    CacheBlock blocks[CACHE_MAX_CAPACITY]; /**< Fixed array of cache blocks. */
    int capacity;                          /**< Configured cache frame capacity. */
    int size;                              /**< Current number of occupied frames. */
    int fifo_index;                        /**< Index pointer for FIFO and Clock policies. */
    int access_counter;                    /**< Monotonic logical clock counter. */
    int last_accessed_slot;                /**< Index of the most recently accessed slot. */

    int hits;   /**< Cumulative hit counter. */
    int misses; /**< Cumulative miss counter. */
} Cache;

/**
 * @brief Initializes a Cache instance with specified capacity.
 * @param cache Pointer to Cache structure.
 * @param capacity Number of cache frames (bounded by CACHE_MAX_CAPACITY).
 */
void cache_init(Cache* cache, int capacity);

/**
 * @brief Accesses a page in cache using First-In, First-Out (FIFO) eviction.
 * @param cache Pointer to Cache structure.
 * @param page_id Target page ID.
 * @param is_write True if write operation.
 * @return True on cache hit, false on cache miss.
 */
bool cache_access_fifo(Cache* cache, int page_id, bool is_write);

/**
 * @brief Accesses a page in cache using Least Recently Used (LRU) eviction.
 * @param cache Pointer to Cache structure.
 * @param page_id Target page ID.
 * @param is_write True if write operation.
 * @return True on cache hit, false on cache miss.
 */
bool cache_access_lru(Cache* cache, int page_id, bool is_write);

/**
 * @brief Accesses a page in cache using Most Recently Used (MRU) eviction.
 * @param cache Pointer to Cache structure.
 * @param page_id Target page ID.
 * @param is_write True if write operation.
 * @return True on cache hit, false on cache miss.
 */
bool cache_access_mru(Cache* cache, int page_id, bool is_write);

/**
 * @brief Accesses a page using Least Frequently Used (LFU) eviction with aging.
 * @param cache Pointer to Cache structure.
 * @param page_id Target page ID.
 * @param is_write True if write operation.
 * @return True on cache hit, false on cache miss.
 */
bool cache_access_lfu(Cache* cache, int page_id, bool is_write);

/**
 * @brief Accesses a page using Belady's Optimal (OPT) lookahead replacement algorithm.
 * @param cache Pointer to Cache structure.
 * @param page_id Target page ID.
 * @param ref_str Array of full reference string sequence.
 * @param ref_len Total length of reference string.
 * @current_idx Index of the current operation in ref_str.
 * @param is_write True if write operation.
 * @return True on cache hit, false on cache miss.
 */
bool cache_access_opt(Cache* cache, int page_id, const int* ref_str, int ref_len, int current_idx,
                      bool is_write);

/**
 * @brief Accesses a page using the Second-Chance (Clock) replacement algorithm.
 * @param cache Pointer to Cache structure.
 * @param page_id Target page ID.
 * @param is_write True if write operation.
 * @return True on cache hit, false on cache miss.
 */
bool cache_access_clock(Cache* cache, int page_id, bool is_write);

/**
 * @brief Accesses a page using the Enhanced Second-Chance algorithm (using reference & dirty bits).
 * @param cache Pointer to Cache structure.
 * @param page_id Target page ID.
 * @param is_write True if write operation.
 * @return True on cache hit, false on cache miss.
 */
bool cache_access_enhanced_clock(Cache* cache, int page_id, bool is_write);

/**
 * @brief Prints current cache slots and statistics to stdout.
 * @param cache Pointer to Cache instance.
 */
void cache_print_status(const Cache* cache);

/**
 * @brief Renders terminal grid visualizer for cache blocks.
 * @param cache Pointer to Cache instance.
 * @param highlighted_slot Target slot index to highlight.
 * @param is_hit True if highlight color should indicate hit (green), else miss (red).
 */
void cache_visualize(const Cache* cache, int highlighted_slot, bool is_hit);

/**
 * @brief Normalizes access counter to prevent integer overflow during prolonged runs.
 * @param cache Pointer to Cache instance.
 */
void cache_normalize_access_counter(Cache* cache);

/**
 * @brief Interactive CLI demo subroutine for the Cache Simulator Suite.
 */
void cache_simulator_demo(void);

#endif // CACHE_H
