#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdbool.h>
#include <stddef.h>

// For Red-Black Tree (Self-Balancing BST)
typedef enum
{
    RED,
    BLACK
} rbColor;

typedef struct rbNode
{
    int data;
    rbColor color;
    struct rbNode* left;
    struct rbNode* right;
    struct rbNode* parent;
} rbNode;

typedef struct rbTree
{
    rbNode* root;
    rbNode* TNULL;
} rbTree;

rbTree* create_rb_tree(void);
void rb_insert(rbTree* tree, int key);
void rb_delete(rbTree* tree, int key);
bool is_rb_tree_valid(rbTree* tree);
void destroy_rb_tree(rbTree* tree);
void red_black_tree_demo(void);

#endif // RED_BLACK_TREE_H
