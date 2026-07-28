#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct HyperLogLog
    {
        uint8_t* registers;
        size_t m;  /* Number of registers: m = 2^b */
        uint8_t b; /* Precision bits (4 <= b <= 16) */
        double alpha_m;
    } HyperLogLog;

    /**
     * @brief Initialize a HyperLogLog cardinality estimator.
     * @param b Number of precision bits (4 <= b <= 16). Number of registers m = 2^b.
     * @return Pointer to initialized HyperLogLog, or NULL on invalid args or error.
     */
    HyperLogLog* hll_init(uint8_t b);

    /**
     * @brief Add an element to the HyperLogLog cardinality estimator.
     * @param hll Pointer to HyperLogLog.
     * @param data Pointer to input data buffer.
     * @param len Byte length of input data.
     * @return true on success, false on invalid args or error.
     */
    bool hll_add(HyperLogLog* hll, const void* data, size_t len);

    /**
     * @brief Estimate the distinct element cardinality.
     * @param hll Pointer to HyperLogLog.
     * @return Estimated number of distinct elements inserted.
     */
    uint64_t hll_count(const HyperLogLog* hll);

    /**
     * @brief Free resources associated with a HyperLogLog estimator.
     * @param hll Pointer to HyperLogLog.
     */
    void hll_free(HyperLogLog* hll);

#ifdef __cplusplus
}
#endif

#endif // HYPERLOGLOG_H
