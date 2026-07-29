#include "rtree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_rtree_init(void)
{
    printf("Running test_rtree_init...\n");
    RTree* tree = rtree_create(4, 2);
    assert(tree != NULL);
    assert(tree->max_entries == 4);
    assert(tree->min_entries == 2);
    assert(tree->total_items == 0);

    rtree_free(tree);
    printf("--> test_rtree_init PASSED!\n");
}

void test_rtree_invalid_args(void)
{
    printf("Running test_rtree_invalid_args...\n");
    assert(rtree_create(1, 1) == NULL);
    assert(rtree_create(4, 3) == NULL);

    RTree* tree = rtree_create(4, 2);
    assert(tree != NULL);

    MBR query = {0.0, 0.0, 10.0, 10.0};
    assert(rtree_insert(NULL, query, NULL) == false);

    RTreeItem* results = NULL;
    assert(rtree_search_mbr(NULL, query, &results) == 0);

    rtree_free(tree);
    rtree_free(NULL);
    printf("--> test_rtree_invalid_args PASSED!\n");
}

void test_rtree_insert_and_split(void)
{
    printf("Running test_rtree_insert_and_split...\n");
    RTree* tree = rtree_create(2, 1); /* Max 2 entries per node */
    assert(tree != NULL);

    MBR b1 = {0.0, 0.0, 2.0, 2.0};
    MBR b2 = {5.0, 5.0, 7.0, 7.0};
    MBR b3 = {10.0, 10.0, 12.0, 12.0};
    MBR b4 = {15.0, 15.0, 17.0, 17.0};

    assert(rtree_insert(tree, b1, NULL) == true);
    assert(rtree_insert(tree, b2, NULL) == true);
    assert(rtree_insert(tree, b3, NULL) == true);
    assert(rtree_insert(tree, b4, NULL) == true);

    assert(tree->total_items == 4);
    assert(tree->root->is_leaf == false);

    rtree_free(tree);
    printf("--> test_rtree_insert_and_split PASSED!\n");
}

void test_rtree_search_mbr(void)
{
    printf("Running test_rtree_search_mbr...\n");
    RTree* tree = rtree_create(4, 2);
    assert(tree != NULL);

    MBR b1 = {1.0, 1.0, 3.0, 3.0};
    MBR b2 = {4.0, 4.0, 6.0, 6.0};
    MBR b3 = {10.0, 10.0, 15.0, 15.0};

    rtree_insert(tree, b1, NULL);
    rtree_insert(tree, b2, NULL);
    rtree_insert(tree, b3, NULL);

    MBR search_query = {0.0, 0.0, 5.0, 5.0};
    RTreeItem* results = NULL;
    size_t count = rtree_search_mbr(tree, search_query, &results);

    assert(count == 2);
    assert(results != NULL);

    free(results);
    rtree_free(tree);
    printf("--> test_rtree_search_mbr PASSED!\n");
}

int main(void)
{
    test_rtree_init();
    test_rtree_invalid_args();
    test_rtree_insert_and_split();
    test_rtree_search_mbr();
    printf("All R-Tree Tests Passed!\n");
    return 0;
}
