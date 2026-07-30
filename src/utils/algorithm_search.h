#ifndef ALGORITHM_SEARCH_H
#define ALGORITHM_SEARCH_H

#include <stdbool.h>
#include <stddef.h>

typedef void (*DemoFuncPtr)(void);

typedef struct AlgorithmEntry
{
    const char* name;
    const char* category;
    const char* keywords;
    int menu_option;
    DemoFuncPtr demo_fn;
} AlgorithmEntry;

typedef struct AlgorithmRegistry
{
    const AlgorithmEntry* entries;
    size_t count;
} AlgorithmRegistry;

/**
 * @brief Retrieve the global static algorithm registry.
 * @return Pointer to AlgorithmRegistry.
 */
const AlgorithmRegistry* get_algorithm_registry(void);

/**
 * @brief Search algorithm registry by case-insensitive query string.
 * @param query Search query term (e.g. "dijkstra", "avl", "sort").
 * @param results Pointer to array of matching AlgorithmEntry pointers.
 * @param max_results Maximum results buffer size.
 * @return Number of matching algorithms found.
 */
size_t search_algorithms(const char* query, const AlgorithmEntry** results, size_t max_results);

#endif // ALGORITHM_SEARCH_H
