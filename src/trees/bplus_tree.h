#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H

#include <stdbool.h>
#include <stddef.h>

// For B+ Tree
typedef struct BPlusNode
{
    bool is_leaf;
    int num_keys;
    int* keys;
    struct BPlusNode** children;
    int* values;
    struct BPlusNode* next;
    struct BPlusNode* prev;
} BPlusNode;

typedef struct BPlusTree
{
    BPlusNode* root;
    int order;
} BPlusTree;

BPlusTree* bplus_tree_create(int order);
void bplus_tree_destroy(BPlusTree* tree);
bool bplus_tree_search(BPlusTree* tree, int key, int* value_out);
bool bplus_tree_insert(BPlusTree* tree, int key, int value);
bool bplus_tree_delete(BPlusTree* tree, int key);
void bplus_tree_range_query(BPlusTree* tree, int lower, int upper);
void bplus_tree_print(BPlusTree* tree);
void bplus_tree_demo(void);

#endif // BPLUS_TREE_H
