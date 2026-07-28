#include "count_min_sketch.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_cms_init(void)
{
    printf("Running test_cms_init...\n");
    CountMinSketch* sketch = cms_init(0.01, 0.01);
    assert(sketch != NULL);
    assert(sketch->width > 0);
    assert(sketch->depth > 0);
    assert(sketch->total_count == 0);

    cms_free(sketch);
    printf("--> test_cms_init PASSED!\n");
}

void test_cms_invalid_args(void)
{
    printf("Running test_cms_invalid_args...\n");
    assert(cms_init(0.0, 0.01) == NULL);
    assert(cms_init(1.0, 0.01) == NULL);
    assert(cms_init(0.01, 0.0) == NULL);
    assert(cms_init(0.01, 1.0) == NULL);

    CountMinSketch* sketch = cms_init(0.05, 0.05);
    assert(sketch != NULL);

    assert(cms_add(NULL, "key", 3, 1) == false);
    assert(cms_add(sketch, NULL, 3, 1) == false);
    assert(cms_add(sketch, "key", 0, 1) == false);
    assert(cms_add(sketch, "key", 3, 0) == false);

    assert(cms_estimate(NULL, "key", 3) == 0);
    assert(cms_estimate(sketch, NULL, 3) == 0);
    assert(cms_estimate(sketch, "key", 0) == 0);

    cms_free(sketch);
    cms_free(NULL);
    printf("--> test_cms_invalid_args PASSED!\n");
}

void test_cms_add_and_estimate(void)
{
    printf("Running test_cms_add_and_estimate...\n");
    CountMinSketch* sketch = cms_init(0.005, 0.01);
    assert(sketch != NULL);

    const char* key1 = "stream_event_A";
    const char* key2 = "stream_event_B";

    assert(cms_add(sketch, key1, strlen(key1), 50) == true);
    assert(cms_add(sketch, key2, strlen(key2), 30) == true);
    assert(cms_add(sketch, key1, strlen(key1), 25) == true);

    uint32_t est1 = cms_estimate(sketch, key1, strlen(key1));
    uint32_t est2 = cms_estimate(sketch, key2, strlen(key2));
    uint32_t est3 = cms_estimate(sketch, "absent_key", 10);

    assert(est1 >= 75);
    assert(est2 >= 30);
    assert(est3 < 10); /* Should be near 0 with small noise */

    cms_free(sketch);
    printf("--> test_cms_add_and_estimate PASSED!\n");
}

void test_cms_stream_frequency_accuracy(void)
{
    printf("Running test_cms_stream_frequency_accuracy...\n");
    CountMinSketch* sketch = cms_init(0.001, 0.01);
    assert(sketch != NULL);

    /* Stream heavy hitter simulation */
    char buf[64];
    for (int i = 0; i < 1000; i++)
    {
        snprintf(buf, sizeof(buf), "user_%d", i % 10);
        assert(cms_add(sketch, buf, strlen(buf), 1) == true);
    }

    /* user_0 should occur exactly 100 times */
    snprintf(buf, sizeof(buf), "user_0");
    uint32_t est = cms_estimate(sketch, buf, strlen(buf));
    printf("Actual count: 100, CMS Estimate: %u\n", est);
    assert(est >= 100);
    assert(est <= 115); /* Within 1.5% relative error */

    cms_free(sketch);
    printf("--> test_cms_stream_frequency_accuracy PASSED!\n");
}

int main(void)
{
    test_cms_init();
    test_cms_invalid_args();
    test_cms_add_and_estimate();
    test_cms_stream_frequency_accuracy();
    printf("All Count-Min Sketch Tests Passed!\n");
    return 0;
}
