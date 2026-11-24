#include "safe_input.h"
#include <stdio.h>
#include <time.h>

// linear_search() returns -1 if element is not present and the index number if the element is
// present

int linear_search(int arr[], int target, int length_of_array);

int linear_search(int arr[], int target, int length_of_array)
{
    if (arr == NULL || length_of_array <= 0)
    {
        return -1;
    }

    for (int i = 0; i < length_of_array; i++)
    {
        if (arr[i] == target)
        {
            return i;
        }
    }
    return -1;
}