#include "fenwick_tree.h"
#include <assert.h>
#include <stdio.h>

void test_create_and_initial_state(void)
{
    FenwickTree* ft = create_fenwick_tree(5);
    assert(ft != NULL);
    assert(ft->size == 5);
    assert(ft->BIT1 != NULL);
    assert(ft->BIT2 != NULL);
    assert(fenwick_range_query(ft, 1, 5) == 0);

    destroy_fenwick_tree(ft);
    printf("Fenwick create and initial state test passed\n");
}

void test_single_update_and_prefix_query(void)
{
    FenwickTree* ft = create_fenwick_tree(5);
    assert(ft != NULL);

    fenwick_range_update(ft, 3, 3, 7);
    assert(fenwick_point_query(ft->BIT1, 3) == 7);
    assert(fenwick_range_query(ft, 1, 3) == 7);
    assert(fenwick_range_query(ft, 3, 3) == 7);
    assert(fenwick_range_query(ft, 4, 5) == 0);

    destroy_fenwick_tree(ft);
    printf("Fenwick single update test passed\n");
}

void test_range_update_and_query(void)
{
    FenwickTree* ft = create_fenwick_tree(5);
    assert(ft != NULL);

    fenwick_range_update(ft, 2, 4, 3);
    assert(fenwick_range_query(ft, 1, 5) == 9);
    assert(fenwick_range_query(ft, 1, 1) == 0);
    assert(fenwick_range_query(ft, 2, 4) == 9);
    assert(fenwick_range_query(ft, 4, 4) == 3);

    destroy_fenwick_tree(ft);
    printf("Fenwick range update test passed\n");
}

void test_invalid_inputs(void)
{
    FenwickTree* ft = create_fenwick_tree(0);
    assert(ft == NULL);

    FenwickTree* null_tree = NULL;
    assert(fenwick_range_query(null_tree, 1, 1) == 0);
    assert(fenwick_point_query(NULL, 3) == 0);

    printf("Fenwick invalid input test passed\n");
}

int main(void)
{
    test_create_and_initial_state();
    test_single_update_and_prefix_query();
    test_range_update_and_query();
    test_invalid_inputs();

    printf("All Fenwick Tree tests passed\n");
    return 0;
}
