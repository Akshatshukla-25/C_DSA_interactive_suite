#include "algorithm_search.h"
#include "display_header.h"
#include "safe_input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declarations of module demo function pointers */
void trees_demo(void);
void graph_traversals_demo(void);
void advanced_graph_algorithms_demo(void);
void sorting_algorithms_n2_demo(void);
void advanced_sorting_demo(void);
void searching_algorithms_demo(void);
void dynamic_programming_demo(void);
void compression_demo(void);
void string_algorithms_demo(void);
void probabilistic_ds_demo(void);
void spatial_indexing_demo(void);

static const AlgorithmEntry GLOBAL_ALGORITHM_TABLE[] = {
    {"Binary Search Tree & AVL Trees", "Trees", "bst binary search tree avl red black splay", 7,
     trees_demo},
    {"Graph Traversals (BFS, DFS, Dijkstra)", "Graph Traversals",
     "bfs dfs dijkstra breadth depth shortest path graph", 5, graph_traversals_demo},
    {"Advanced Graph Algorithms (Flow, Matching, SCC)", "Advanced Graphs",
     "dinic ford fulkerson edmonds karp scc bipartite matching", 6, advanced_graph_algorithms_demo},
    {"O(N^2) Sorting Algorithms Suite", "Sorting", "bubble insertion selection sort elementary", 3,
     sorting_algorithms_n2_demo},
    {"O(N log N) Advanced Sorting Algorithms Suite", "Sorting",
     "quick merge heap radix sort divide conquer", 3, advanced_sorting_demo},
    {"Searching Algorithms Suite", "Searching", "binary linear interpolation exponential search", 4,
     searching_algorithms_demo},
    {"Dynamic Programming Algorithms Suite", "Dynamic Programming",
     "knapsack lcs mcm fibonacci coin change edit distance dp", 8, dynamic_programming_demo},
    {"String Processing & Compression Algorithms", "String & Compression",
     "huffman rle lzw bwt kmp rabin karp string compression", 12, compression_demo},
    {"Probabilistic Data Structures (Bloom, CM-Sketch, HLL)", "Probabilistic DS",
     "bloom filter count min sketch hyperloglog hll probabilistic", 16, probabilistic_ds_demo},
    {"Spatial & Multi-Dimensional Indexing (k-d Tree, QuadTree, R-Tree)", "Spatial Indexing",
     "kd kdtree quadtree rtree spatial 2d mbr point range search", 17, spatial_indexing_demo}};

static const AlgorithmRegistry GLOBAL_REGISTRY = {
    GLOBAL_ALGORITHM_TABLE, sizeof(GLOBAL_ALGORITHM_TABLE) / sizeof(GLOBAL_ALGORITHM_TABLE[0])};

const AlgorithmRegistry* get_algorithm_registry(void)
{
    return &GLOBAL_REGISTRY;
}

static bool string_contains_case_insensitive(const char* haystack, const char* needle)
{
    if (!haystack || !needle)
    {
        return false;
    }

    size_t haystack_len = strlen(haystack);
    size_t needle_len = strlen(needle);
    if (needle_len == 0 || needle_len > haystack_len)
    {
        return false;
    }

    for (size_t i = 0; i <= haystack_len - needle_len; i++)
    {
        bool match = true;
        for (size_t j = 0; j < needle_len; j++)
        {
            if (tolower((unsigned char)haystack[i + j]) != tolower((unsigned char)needle[j]))
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            return true;
        }
    }
    return false;
}

size_t search_algorithms(const char* query, const AlgorithmEntry** results, size_t max_results)
{
    if (!query || !results || max_results == 0)
    {
        return 0;
    }

    size_t found = 0;
    const AlgorithmRegistry* reg = get_algorithm_registry();

    for (size_t i = 0; i < reg->count && found < max_results; i++)
    {
        const AlgorithmEntry* entry = &reg->entries[i];
        if (string_contains_case_insensitive(entry->name, query) ||
            string_contains_case_insensitive(entry->category, query) ||
            string_contains_case_insensitive(entry->keywords, query))
        {
            results[found++] = entry;
        }
    }

    return found;
}

void run_algorithm_search_menu(void)
{
    display_header("Interactive Algorithm Quick-Search Finder");

    char query[64] = {0};
    int status =
        safe_input_string(query, "\nEnter search keyword (e.g. 'dijkstra', 'avl', 'sort'): ");
    if (status == INPUT_EXIT_SIGNAL || strlen(query) == 0)
    {
        printf("\nExiting interactive algorithm finder...\n");
        return;
    }

    const AlgorithmEntry* results[20];
    size_t count = search_algorithms(query, results, 20);

    if (count == 0)
    {
        printf("\nNo algorithms matching '%s' were found in the registry.\n", query);
        printf("\nExiting interactive algorithm finder...\n");
        return;
    }

    printf("\nFound %zu matching algorithm demo(s):\n", count);
    for (size_t i = 0; i < count; i++)
    {
        printf("  %zu. %s [%s] (Menu Option %d)\n", i + 1, results[i]->name, results[i]->category,
               results[i]->menu_option);
    }

    int choice;
    status = safe_input_int(&choice, "\nSelect algorithm number to launch demo (-1 to cancel): ", 1,
                            (int)count);
    if (status == INPUT_EXIT_SIGNAL || choice < 1 || (size_t)choice > count)
    {
        printf("\nExiting interactive algorithm finder...\n");
        return;
    }

    printf("\nLaunching '%s' demo...\n\n", results[choice - 1]->name);
    if (results[choice - 1]->demo_fn)
    {
        results[choice - 1]->demo_fn();
    }
}
