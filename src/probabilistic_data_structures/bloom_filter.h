#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct BloomFilter
    {
        uint8_t* bit_array;
        size_t bit_size;
        size_t num_hashes;
        size_t count;
        size_t expected_items;
        double target_fp_rate;
    } BloomFilter;

    /**
     * @brief Initialize a Bloom Filter with optimal parameters.
     * @param expected_items Expected number of elements to insert.
     * @param false_positive_rate Desired probability of false positives (0.0 < p < 1.0).
     * @return Pointer to initialized BloomFilter, or NULL on failure.
     */
    BloomFilter* bloom_init(size_t expected_items, double false_positive_rate);

    /**
     * @brief Insert an element into the Bloom Filter.
     * @param filter Pointer to BloomFilter.
     * @param data Pointer to input data buffer.
     * @param len Byte length of input data.
     * @return true on success, false on NULL input or error.
     */
    bool bloom_add(BloomFilter* filter, const void* data, size_t len);

    /**
     * @brief Check if an element is potentially in the Bloom Filter.
     * @param filter Pointer to BloomFilter.
     * @param data Pointer to input data buffer.
     * @param len Byte length of input data.
     * @return true if element MAY be present, false if element is DEFINITELY not present.
     */
    bool bloom_check(const BloomFilter* filter, const void* data, size_t len);

    /**
     * @brief Free resources associated with a Bloom Filter.
     * @param filter Pointer to BloomFilter.
     */
    void bloom_free(BloomFilter* filter);

    uint64_t bloom_fnv1a_hash(const void* data, size_t len, uint64_t seed);

#ifdef __cplusplus
}
#endif

#endif // BLOOM_FILTER_H
