#include "hash.h"
#include <assert.h>
#include <stdio.h>

void test_hash_range()
{
    for (int size = 1; size <= 100; size++)
    {
        for (int value = 0; value <= 1000; value++)
        {
            int h = hash_function(value, size);
            assert(h >= 0);
            assert(h < size);
        }
    }
    printf("Hash range test passed\n");
}

void test_hash_deterministic()
{
    for (int size = 1; size <= 50; size++)
    {
        for (int value = 0; value <= 100; value++)
        {
            int h1 = hash_function(value, size);
            int h2 = hash_function(value, size);
            assert(h1 == h2);
        }
    }
    printf("Hash determinism test passed\n");
}

void test_hash_basic_behavior()
{
    int size = 10;

    int h1 = hash_function(5, size);
    int h2 = hash_function(15, size);

    assert(h1 >= 0 && h1 < size);
    assert(h2 >= 0 && h2 < size);

    printf("Hash basic behavior test passed\n");
}

void test_hash_advanced_edge_cases()
{
    /* Negative values and large table sizes */
    for (int size = 10; size <= 1000; size *= 10)
    {
        for (int value = -500; value <= 0; value++)
        {
            int h = hash_function(value, size);
            assert(h >= 0);
            assert(h < size);
        }
    }

    /* Single element size boundary */
    assert(hash_function(0, 1) == 0);
    assert(hash_function(999, 1) == 0);

    /* Consecutive integer hash distribution */
    int counts[10] = {0};
    for (int i = 0; i < 100; i++)
    {
        int slot = hash_function(i, 10);
        counts[slot]++;
    }
    for (int k = 0; k < 10; k++)
    {
        assert(counts[k] == 10);
    }

    printf("Hash advanced edge case tests passed\n");
}

int main()
{
    test_hash_range();
    test_hash_deterministic();
    test_hash_basic_behavior();
    test_hash_advanced_edge_cases();

    printf("All hash function tests passed\n");
    return 0;
}