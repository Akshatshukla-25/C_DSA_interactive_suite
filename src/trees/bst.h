#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Node structure for Binary Search Tree (BST).
 */
typedef struct bstNode
{
    int data;              /**< Integer payload data. */
    struct bstNode* left;  /**< Pointer to left child subtree. */
    struct bstNode* right; /**< Pointer to right child subtree. */
} bstNode;

/** @brief Runs the interactive Binary Search Tree demonstration module. */
void binary_search_tree_demo(void);

/**
 * @brief Performs level-order (breadth-first) traversal printing to stdout.
 * @param head Pointer to the root node.
 */
void bst_level_order(struct bstNode* head);

/**
 * @brief Renders 2D ASCII graphical representation of the tree to stdout.
 * @param root Pointer to root node.
 */
void bst_print_ascii(const bstNode* root);

/**
 * @brief Inserts an integer value into the Binary Search Tree.
 * @param head_ref Double pointer to root node pointer.
 * @param value Integer value to insert.
 * @return 1 on success, 0 if value already exists, -1 on allocation failure.
 */
int bst_insert(bstNode** head_ref, int value);

/**
 * @brief Performs in-order traversal (Left, Root, Right).
 * @param head Pointer to root node.
 */
void bst_inorder(const bstNode* head);

/**
 * @brief Performs pre-order traversal (Root, Left, Right).
 * @param head Pointer to root node.
 */
void bst_preorder(const bstNode* head);

/**
 * @brief Performs post-order traversal (Left, Right, Root).
 * @param head Pointer to root node.
 */
void bst_postorder(const bstNode* head);

/**
 * @brief Counts the total number of nodes in the tree.
 * @param head Pointer to root node.
 * @return Total node count.
 */
int countnodes(const bstNode* head);

/**
 * @brief Calculates height (maximum depth) of the tree.
 * @param root Pointer to root node.
 * @return Height of tree (0 if empty).
 */
int tree_height(const bstNode* root);

/**
 * @brief Recursively frees all nodes in the Binary Search Tree.
 * @param head Pointer to root node.
 */
void destroy_bst(bstNode* head);

/**
 * @brief Deletes a node with specified target value from the tree.
 * @param root Pointer to root node.
 * @param value Integer value to delete.
 * @return Pointer to updated root node.
 */
bstNode* bst_delete(bstNode* root, int value);

#endif // BST_H
