#include "trees.h"
#include <assert.h>
#include <stdio.h>

void test_create_and_insert(void)
{
    rbTree* tree = create_rb_tree();
    assert(tree != NULL);
    assert(tree->root == tree->TNULL);

    rb_insert(tree, 10);
    rb_insert(tree, 5);
    rb_insert(tree, 15);
    rb_insert(tree, 12);
    rb_insert(tree, 20);

    assert(tree->root != tree->TNULL);
    assert(tree->root->data == 10 || tree->root->data == 5 || tree->root->data == 15);
    assert(tree->root->color == BLACK);
    assert(is_rb_tree_valid(tree) == true);

    destroy_rb_tree(tree);
    printf("Red-Black create and insert test passed\n");
}

void test_duplicate_and_repeated_insertions(void)
{
    rbTree* tree = create_rb_tree();
    assert(tree != NULL);

    rb_insert(tree, 7);
    rb_insert(tree, 3);
    rb_insert(tree, 18);
    rb_insert(tree, 10);
    rb_insert(tree, 22);
    rb_insert(tree, 3);

    assert(is_rb_tree_valid(tree) == true);
    assert(tree->root != tree->TNULL);

    destroy_rb_tree(tree);
    printf("Red-Black repeated insertion test passed\n");
}

int main(void)
{
    test_create_and_insert();
    test_duplicate_and_repeated_insertions();

    printf("All Red-Black Tree tests passed\n");
    return 0;
}
