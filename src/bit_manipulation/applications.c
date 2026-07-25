#include "bit_manipulation.h"
#include <stdio.h>

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

/**
 * Generates and prints all subsets (power set) of an array using bitmasking.
 * For a set of size n, there are 2^n subsets. Each number from 0 to (2^n - 1)
 * acts as a bitmask: if the j-th bit is set, then arr[j] is included in the subset.
 * Time complexity: O(n * 2^n), Space complexity: O(1).
 */
void generate_subsets(int arr[], int n)
{
    int total_subsets = (1 << n);

    for (int mask = 0; mask < total_subsets; mask++)
    {
        printf("{ ");
        for (int j = 0; j < n; j++)
        {
            if (mask & (1 << j))
            {
                printf("%d ", arr[j]);
            }
        }
        printf("}\n");
    }
}
