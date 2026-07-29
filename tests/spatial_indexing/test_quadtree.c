#include "quadtree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_quadtree_init(void)
{
    printf("Running test_quadtree_init...\n");
    Rect boundary = {0.0, 0.0, 100.0, 100.0};
    QuadTree* tree = quadtree_create(boundary, 4);
    assert(tree != NULL);
    assert(tree->capacity == 4);
    assert(tree->total_points == 0);

    quadtree_free(tree);
    printf("--> test_quadtree_init PASSED!\n");
}

void test_quadtree_invalid_args(void)
{
    printf("Running test_quadtree_invalid_args...\n");
    Rect invalid_b = {0.0, 0.0, 0.0, 100.0};
    assert(quadtree_create(invalid_b, 4) == NULL);

    Rect b = {0.0, 0.0, 100.0, 100.0};
    assert(quadtree_create(b, 0) == NULL);

    QuadTree* tree = quadtree_create(b, 4);
    assert(tree != NULL);

    /* Point outside boundary */
    assert(quadtree_insert(tree, 500.0, 500.0, NULL) == false);

    QuadPoint* results = NULL;
    assert(quadtree_query_range(NULL, b, &results) == 0);

    quadtree_free(tree);
    quadtree_free(NULL);
    printf("--> test_quadtree_invalid_args PASSED!\n");
}

void test_quadtree_insert_and_split(void)
{
    printf("Running test_quadtree_insert_and_split...\n");
    Rect boundary = {0.0, 0.0, 100.0, 100.0};
    QuadTree* tree = quadtree_create(boundary, 2); /* Capacity 2 forces split */
    assert(tree != NULL);

    assert(quadtree_insert(tree, 10.0, 10.0, NULL) == true);
    assert(quadtree_insert(tree, -20.0, -20.0, NULL) == true);
    assert(quadtree_insert(tree, 30.0, -30.0, NULL) == true);
    assert(quadtree_insert(tree, -40.0, 40.0, NULL) == true);

    assert(tree->total_points == 4);
    assert(tree->root->divided == true);

    quadtree_free(tree);
    printf("--> test_quadtree_insert_and_split PASSED!\n");
}

void test_quadtree_range_query(void)
{
    printf("Running test_quadtree_range_query...\n");
    Rect boundary = {0.0, 0.0, 100.0, 100.0};
    QuadTree* tree = quadtree_create(boundary, 4);
    assert(tree != NULL);

    quadtree_insert(tree, 10.0, 10.0, NULL);
    quadtree_insert(tree, 20.0, 20.0, NULL);
    quadtree_insert(tree, -50.0, -50.0, NULL);
    quadtree_insert(tree, 80.0, 80.0, NULL);

    Rect query_range = {15.0, 15.0, 15.0, 15.0}; /* [0, 30] x [0, 30] */
    QuadPoint* results = NULL;
    size_t count = quadtree_query_range(tree, query_range, &results);

    assert(count == 2);
    assert(results != NULL);

    free(results);
    quadtree_free(tree);
    printf("--> test_quadtree_range_query PASSED!\n");
}

int main(void)
{
    test_quadtree_init();
    test_quadtree_invalid_args();
    test_quadtree_insert_and_split();
    test_quadtree_range_query();
    printf("All QuadTree Tests Passed!\n");
    return 0;
}
