#include "kd_tree.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test_kdtree_init(void)
{
    printf("Running test_kdtree_init...\n");
    KDTree* tree = kdtree_create(2);
    assert(tree != NULL);
    assert(tree->k == 2);
    assert(tree->count == 0);
    assert(tree->root == NULL);

    kdtree_free(tree);
    printf("--> test_kdtree_init PASSED!\n");
}

void test_kdtree_invalid_args(void)
{
    printf("Running test_kdtree_invalid_args...\n");
    assert(kdtree_create(0) == NULL);
    assert(kdtree_create(-1) == NULL);

    KDTree* tree = kdtree_create(2);
    assert(tree != NULL);

    double pt[2] = {1.0, 2.0};
    assert(kdtree_insert(NULL, pt, NULL) == false);
    assert(kdtree_insert(tree, NULL, NULL) == false);

    assert(kdtree_nearest_neighbor(NULL, pt, NULL) == NULL);
    assert(kdtree_nearest_neighbor(tree, NULL, NULL) == NULL);

    KDNode** res = NULL;
    assert(kdtree_range_search(NULL, pt, pt, &res) == 0);

    kdtree_free(tree);
    kdtree_free(NULL);
    printf("--> test_kdtree_invalid_args PASSED!\n");
}

void test_kdtree_insert_and_nn(void)
{
    printf("Running test_kdtree_insert_and_nn...\n");
    KDTree* tree = kdtree_create(2);
    assert(tree != NULL);

    double points[][2] = {{3.0, 6.0},  {17.0, 15.0}, {13.0, 15.0},
                          {6.0, 12.0}, {9.0, 1.0},   {2.0, 7.0}};
    size_t num_points = sizeof(points) / sizeof(points[0]);

    for (size_t i = 0; i < num_points; i++)
    {
        assert(kdtree_insert(tree, points[i], NULL) == true);
    }
    assert(tree->count == num_points);

    /* Query nearest neighbor to (9.0, 2.0) -> expected (9.0, 1.0) with dist 1.0 */
    double query[2] = {9.0, 2.0};
    double dist = 0.0;
    KDNode* nearest = kdtree_nearest_neighbor(tree, query, &dist);
    assert(nearest != NULL);
    assert(nearest->point[0] == 9.0 && nearest->point[1] == 1.0);
    assert(fabs(dist - 1.0) < 1e-6);

    kdtree_free(tree);
    printf("--> test_kdtree_insert_and_nn PASSED!\n");
}

void test_kdtree_range_search(void)
{
    printf("Running test_kdtree_range_search...\n");
    KDTree* tree = kdtree_create(2);
    assert(tree != NULL);

    double points[][2] = {{2.0, 3.0}, {5.0, 4.0}, {9.0, 6.0}, {4.0, 7.0}, {8.0, 1.0}};
    for (size_t i = 0; i < 5; i++)
    {
        kdtree_insert(tree, points[i], NULL);
    }

    double min_pt[2] = {3.0, 3.0};
    double max_pt[2] = {9.0, 7.0};
    KDNode** results = NULL;
    size_t count = kdtree_range_search(tree, min_pt, max_pt, &results);

    /* Points in [3,9]x[3,7] should be (5,4), (9,6), (4,7) -> 3 points */
    assert(count == 3);
    assert(results != NULL);

    free(results);
    kdtree_free(tree);
    printf("--> test_kdtree_range_search PASSED!\n");
}

int main(void)
{
    test_kdtree_init();
    test_kdtree_invalid_args();
    test_kdtree_insert_and_nn();
    test_kdtree_range_search();
    printf("All k-d Tree Tests Passed!\n");
    return 0;
}
