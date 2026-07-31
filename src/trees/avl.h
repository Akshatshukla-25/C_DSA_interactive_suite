#ifndef AVL_H
#define AVL_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Node structure for AVL Tree (Self-Balancing Binary Search Tree).
 */
typedef struct avlNode
{
    int data;              /**< Integer payload data. */
    int height;            /**< Subtree height for balance factor calculations. */
    struct avlNode* left;  /**< Pointer to left child subtree. */
    struct avlNode* right; /**< Pointer to right child subtree. */
} avlNode;

/**
 * @brief Inserts an integer value into the AVL Tree and maintains balance.
 * @param root_ref Double pointer to root node.
 * @param value Integer value to insert.
 * @return 1 on success, 0 if duplicate, -1 on allocation failure.
 */
int avl_insert(avlNode** root_ref, int value);

/**
 * @brief Deletes an integer value from the AVL Tree and rebalances.
 * @param root_ref Double pointer to root node.
 * @param value Integer value to delete.
 * @return 1 on success, 0 if not found.
 */
int avl_delete(avlNode** root_ref, int value);

/**
 * @brief Safely computes height of an AVL node (returns 0 for NULL).
 * @param node Pointer to target AVL node.
 * @return Node height value.
 */
int avl_height(const avlNode* node);

/**
 * @brief Calculates balance factor (left_height - right_height).
 * @param node Pointer to target AVL node.
 * @return Balance factor value.
 */
int avl_balance_factor(const avlNode* node);

/**
 * @brief Performs in-order traversal of the AVL Tree.
 * @param root Pointer to root node.
 */
void avl_inorder(const avlNode* root);

/**
 * @brief Performs pre-order traversal of the AVL Tree.
 * @param root Pointer to root node.
 */
void avl_preorder(const avlNode* root);

/**
 * @brief Performs post-order traversal of the AVL Tree.
 * @param root Pointer to root node.
 */
void avl_postorder(const avlNode* root);

/**
 * @brief Recursively frees all nodes in the AVL Tree.
 * @param root Pointer to root node.
 */
void destroy_avl(avlNode* root);

/** @brief Runs the interactive AVL Tree demonstration module. */
void avl_demo(void);

#endif // AVL_H
