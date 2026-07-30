#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

// For Binary Search Tree
typedef struct bstNode
{
    int data;
    struct bstNode* left;
    struct bstNode* right;
} bstNode;

void binary_search_tree_demo(void);
void bst_level_order(struct bstNode* head);
void bst_print_ascii(const bstNode* root);
int bst_insert(bstNode** head_ref, int value);
void bst_inorder(const bstNode* head);
void bst_preorder(const bstNode* head);
void bst_postorder(const bstNode* head);
int countnodes(const bstNode* head);
int tree_height(const bstNode* root);
void destroy_bst(bstNode* head);
bstNode* bst_delete(bstNode* root, int value);

#endif // BST_H
