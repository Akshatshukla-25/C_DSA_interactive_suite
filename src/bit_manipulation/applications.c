#include "bit_manipulation.h"

/**
 * Finds the unique element in an array where every other element appears exactly twice.
 * Uses XOR bit manipulation to achieve O(n) time complexity and O(1) space complexity.
 */
int find_unique(int arr[], int n)
{
    int unique = 0;
    for (int i = 0; i < n; i++)
    {
        unique ^= arr[i];
    }
    return unique;
}
