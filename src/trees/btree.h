#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stddef.h>

// For B-Tree
#define BTREE_MAX_DEGREE 10

typedef struct btreeNode
{
    int keys[2 * BTREE_MAX_DEGREE - 1];
    struct btreeNode* children[2 * BTREE_MAX_DEGREE];
    int num_keys;
    int is_leaf;
} btreeNode;

btreeNode* btree_create_node(int is_leaf);
int btree_insert(btreeNode** root_ref, int key, int t);
int btree_search(btreeNode* root, int key);
void btree_traverse(const btreeNode* root);
btreeNode* btree_delete(btreeNode* root, int key, int t);
void btree_destroy(btreeNode* root);
void btree_demo(void);

#endif // BTREE_H
