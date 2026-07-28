#ifndef COUNT_MIN_SKETCH_H
#define COUNT_MIN_SKETCH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct CountMinSketch
    {
        uint32_t** table;
        size_t width; /* w = ceil(e / epsilon) */
        size_t depth; /* d = ceil(ln(1 / delta)) */
        size_t total_count;
        double epsilon;
        double delta;
    } CountMinSketch;

    /**
     * @brief Initialize a Count-Min Sketch frequency estimator.
     * @param epsilon Relative error factor (0.0 < epsilon < 1.0), controls width.
     * @param delta Probability of error (0.0 < delta < 1.0), controls depth.
     * @return Pointer to initialized CountMinSketch, or NULL on error.
     */
    CountMinSketch* cms_init(double epsilon, double delta);

    /**
     * @brief Add an item count increment to the Count-Min Sketch.
     * @param sketch Pointer to CountMinSketch.
     * @param data Pointer to input item buffer.
     * @param len Byte length of input item.
     * @param count Increment count (usually 1 or positive value).
     * @return true on success, false on invalid args or error.
     */
    bool cms_add(CountMinSketch* sketch, const void* data, size_t len, uint32_t count);

    /**
     * @brief Estimate the frequency of an item in the data stream.
     * @param sketch Pointer to CountMinSketch.
     * @param data Pointer to input item buffer.
     * @param len Byte length of input item.
     * @return Upper bound estimate of the item's frequency.
     */
    uint32_t cms_estimate(const CountMinSketch* sketch, const void* data, size_t len);

    /**
     * @brief Free resources associated with a Count-Min Sketch.
     * @param sketch Pointer to CountMinSketch.
     */
    void cms_free(CountMinSketch* sketch);

#ifdef __cplusplus
}
#endif

#endif // COUNT_MIN_SKETCH_H
