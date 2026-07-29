#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include <stddef.h>

// For AVL Tree (Self-Balancing Binary Search Tree)
typedef struct avlNode
{
    int data;
    int height;
    struct avlNode* left;
    struct avlNode* right;
} avlNode;

int avl_insert(avlNode** root_ref, int value);
int avl_delete(avlNode** root_ref, int value);
int avl_height(const avlNode* node);
int avl_balance_factor(const avlNode* node);
void avl_inorder(const avlNode* root);
void avl_preorder(const avlNode* root);
void avl_postorder(const avlNode* root);
void destroy_avl(avlNode* root);
void avl_demo(void);

#endif // AVL_H
