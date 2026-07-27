#include "trees.h"
#include <assert.h>
#include <stdio.h>

void test_empty_tree(void)
{
    splayNode* root = NULL;

    assert(splay_tree_search(root, 10) == NULL);
    assert(splay_tree_delete(root, 10) == NULL);

    destroy_splay_tree(root);
    printf("Splay empty tree test passed\n");
}

void test_insert_and_search(void)
{
    splayNode* root = NULL;

    root = splay_tree_insert(root, 10);
    root = splay_tree_insert(root, 20);
    root = splay_tree_insert(root, 30);

    assert(root != NULL);
    assert(root->key == 30);

    root = splay_tree_search(root, 10);
    assert(root != NULL);
    assert(root->key == 10);

    destroy_splay_tree(root);
    printf("Splay insert and search test passed\n");
}

void test_delete_and_root_rotation(void)
{
    splayNode* root = NULL;

    root = splay_tree_insert(root, 10);
    root = splay_tree_insert(root, 20);
    root = splay_tree_insert(root, 30);

    root = splay_tree_delete(root, 20);
    assert(root != NULL);
    assert(root->key != 20);

    root = splay_tree_search(root, 30);
    assert(root != NULL);
    assert(root->key == 30);

    destroy_splay_tree(root);
    printf("Splay delete and root rotation test passed\n");
}

int main(void)
{
    test_empty_tree();
    test_insert_and_search();
    test_delete_and_root_rotation();

    printf("All Splay Tree tests passed\n");
    return 0;
}
