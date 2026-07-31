#include "algorithm_search.h"
#include "display_header.h"
#include "safe_input.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forward declarations of demo function pointers */
void trees_demo(void);
void binary_search_tree_demo(void);
void avl_demo(void);
void TBT_demo(void);
void trie_demo(void);
void btree_demo(void);
void bplus_tree_demo(void);
void segment_tree_demo(void);
void fenwick_tree_demo(void);
void splay_tree_demo(void);
void red_black_tree_demo(void);

void advanced_heaps_demo(void);
void run_binomial_demo(void);
void run_dary_demo(void);
void run_fibonacci_demo(void);
void run_leftist_demo(void);
void run_skew_demo(void);
void run_min_max_demo(void);
void run_treap_demo(void);

void sorting_algorithms_n2_demo(void);
void bubble_sort_optimized_demo(void);
void insertion_sort_demo(void);
void selection_sort_demo(void);
void shell_sort_demo(void);

void advanced_sorting_demo(void);
void quicksort_demo(void);
void merge_sort_demo(void);
void heap_sort_demo(void);
void radix_sort_demo(void);
void bucket_sort_demo(void);

void searching_algorithms_demo(void);
void graph_traversals_demo(void);
void advanced_graph_algorithms_demo(void);
void dynamic_programming_demo(void);
void compression_demo(void);
void string_algorithms_demo(void);
void probabilistic_ds_demo(void);
void spatial_indexing_demo(void);

static const AlgorithmEntry GLOBAL_ALGORITHM_TABLE[] = {
    /* Trees Category */
    {"Binary Search Tree (BST) Interactive Demo", "Trees",
     "bst binary search tree node insert delete search", 7, binary_search_tree_demo},
    {"AVL Self-Balancing Tree Interactive Demo", "Trees",
     "avl tree balance factor rotations self balancing search", 7, avl_demo},
    {"Threaded Binary Tree (TBT) Interactive Demo", "Trees",
     "threaded tbt binary tree traversal null pointers", 7, TBT_demo},
    {"Trie Prefix Tree Interactive Demo", "Trees",
     "trie prefix tree string dictionary auto complete search", 7, trie_demo},
    {"B-Tree Self-Balancing Search Tree Demo", "Trees",
     "btree b-tree multiway disk storage database index", 7, btree_demo},
    {"B+ Tree Indexing Interactive Demo", "Trees",
     "bplus b+tree sequential leaf range query database index", 7, bplus_tree_demo},
    {"Segment Tree Range Query Interactive Demo", "Trees",
     "segment tree range query min max sum update array", 7, segment_tree_demo},
    {"Fenwick Tree (Binary Indexed Tree) Demo", "Trees",
     "fenwick bit binary indexed tree prefix sum point update", 7, fenwick_tree_demo},
    {"Splay Tree Self-Adjusting Search Tree Demo", "Trees",
     "splay tree self adjusting cache recent access search", 7, splay_tree_demo},
    {"Red-Black Balanced Search Tree Demo", "Trees",
     "red black tree rbt color balance self balancing search", 7, red_black_tree_demo},
    {"Trees & Advanced Tree Structures Suite", "Trees",
     "bst avl red black splay segment fenwick trie btree", 7, trees_demo},

    /* Advanced Heaps Category */
    {"Binomial Heap Priority Queue Demo", "Advanced Heaps",
     "binomial heap priority queue merge union min heap", 9, run_binomial_demo},
    {"D-ary Heap Multi-way Priority Queue Demo", "Advanced Heaps",
     "dary d-ary heap multiway priority queue min heap", 9, run_dary_demo},
    {"Fibonacci Heap Amortized Priority Queue Demo", "Advanced Heaps",
     "fibonacci heap priority queue amortized decrease key min heap", 9, run_fibonacci_demo},
    {"Leftist Heap Meldable Priority Queue Demo", "Advanced Heaps",
     "leftist heap meldable priority queue merge null path length", 9, run_leftist_demo},
    {"Skew Heap Self-Adjusting Priority Queue Demo", "Advanced Heaps",
     "skew heap self adjusting meldable priority queue merge", 9, run_skew_demo},
    {"Min-Max Double-Ended Priority Queue Demo", "Advanced Heaps",
     "min max min-max heap double ended priority queue depq", 9, run_min_max_demo},
    {"Treap Randomized Search Tree & Heap Demo", "Advanced Heaps",
     "treap randomized binary search tree priority heap cartesian", 9, run_treap_demo},
    {"Advanced Heaps & Priority Queues Suite", "Advanced Heaps",
     "heaps binomial fibonacci dary leftist skew treap minmax", 9, advanced_heaps_demo},

    /* Searching & Sorting Category */
    {"Bubble Sort Interactive Demo", "Sorting", "bubble sort elementary exchange n2", 3,
     bubble_sort_optimized_demo},
    {"Selection Sort Interactive Demo", "Sorting", "selection sort elementary select minimum n2", 3,
     selection_sort_demo},
    {"Insertion Sort Interactive Demo", "Sorting", "insertion sort elementary insert online n2", 3,
     insertion_sort_demo},
    {"Shell Sort Diminishing Increment Demo", "Sorting",
     "shell sort diminishing increment gap insertion n2", 3, shell_sort_demo},
    {"O(N^2) Elementary Sorting Suite", "Sorting",
     "bubble selection insertion shell sort elementary n2", 3, sorting_algorithms_n2_demo},

    {"Quick Sort Divide & Conquer Demo", "Sorting",
     "quick sort partition divide conquer pivot nlogn", 3, quicksort_demo},
    {"Merge Sort Stable Sorting Demo", "Sorting",
     "merge sort divide conquer stable sub arrays nlogn", 3, merge_sort_demo},
    {"Heap Sort In-place Comparison Demo", "Sorting",
     "heap sort binary heap in place priority nlogn", 3, heap_sort_demo},
    {"Radix Sort Non-comparison Integer Sorting Demo", "Sorting",
     "radix sort counting digit non comparison linear", 3, radix_sort_demo},
    {"Bucket Sort Distribution Sorting Demo", "Sorting",
     "bucket sort distribution floating point linear", 3, bucket_sort_demo},
    {"O(N log N) Advanced Sorting Suite", "Sorting",
     "quick merge heap radix bucket sort advanced nlogn", 3, advanced_sorting_demo},

    {"Searching Algorithms Suite (Binary, Linear, Jump, Interpolation)", "Searching",
     "binary linear interpolation jump exponential search", 4, searching_algorithms_demo},

    /* Other Category Modules */
    {"Graph Traversals (BFS, DFS, Dijkstra)", "Graph Traversals",
     "bfs dfs dijkstra breadth depth shortest path graph", 5, graph_traversals_demo},
    {"Advanced Graph Algorithms (Flow, Matching, SCC, Bridges)", "Advanced Graphs",
     "dinic ford fulkerson edmonds karp scc bipartite matching bridges articulation", 6,
     advanced_graph_algorithms_demo},
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

    const AlgorithmEntry* results[40];
    size_t count = search_algorithms(query, results, 40);

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
