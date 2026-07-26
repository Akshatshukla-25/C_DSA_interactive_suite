#include "hash.h"
#include "safe_input.h"
#include "sll.h"
#include <stdio.h>
#include <string.h>

bool separate_chaining_insert(Node* table[], int length_of_array, int value)
{
    if (length_of_array <= 0 || table == NULL)
    {
        return false;
    }

    int hash_location = hash_function(value, length_of_array);
    if (hash_location == -1)
    {
        return false;
    }

    sll_insertAtEnd(&table[hash_location], (void*)(intptr_t)value);
    return true;
}
