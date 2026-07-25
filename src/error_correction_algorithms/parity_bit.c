#include "error_correction_algorithms.h"
#include "safe_input.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* Helper to validate if a string is a non-empty binary string */
static bool validate_binary_string(const char* data)
{
    if (!data || strlen(data) == 0)
    {
        return false;
    }

    for (size_t i = 0; i < strlen(data); i++)
    {
        if (data[i] != '0' && data[i] != '1')
        {
            return false;
        }
    }

    return true;
}

/* Helper to count number of 1s */
static int count_ones(const char* data)
{
    int count = 0;

    for (size_t i = 0; i < strlen(data); i++)
    {
        if (data[i] == '1')
        {
            count++;
        }
    }

    return count;
}

/* Even parity generator */
int generateEvenParity(const char* data)
{
    if (!validate_binary_string(data))
    {
        return -1;
    }

    int ones = count_ones(data);
    return (ones % 2 == 0) ? 0 : 1;
}

/* Odd parity generator */
int generateOddParity(const char* data)
{
    if (!validate_binary_string(data))
    {
        return -1;
    }

    int ones = count_ones(data);
    return (ones % 2 == 0) ? 1 : 0;
}

/* Even parity verification */
int verifyEvenParity(const char* receivedData)
{
    if (!validate_binary_string(receivedData))
    {
        return -1;
    }

    int ones = count_ones(receivedData);
    return (ones % 2 == 0) ? 1 : 0;
}

/* Odd parity verification */
int verifyOddParity(const char* receivedData)
{
    if (!validate_binary_string(receivedData))
    {
        return -1;
    }

    int ones = count_ones(receivedData);
    return (ones % 2 == 1) ? 1 : 0;
}
