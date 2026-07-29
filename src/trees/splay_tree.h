#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <stdbool.h>
#include <stddef.h>

// For Splay Tree (Self-Adjusting Binary Search Tree)
typedef struct splayNode
{
    int key;
    struct splayNode* left;
    struct splayNode* right;
} splayNode;

splayNode* splay_create_node(int key);
splayNode* splay_tree_splay(splayNode* root, int key);
splayNode* splay_tree_search(splayNode* root, int key);
splayNode* splay_tree_insert(splayNode* root, int key);
splayNode* splay_tree_delete(splayNode* root, int key);
void splay_tree_preorder(splayNode* root);
void destroy_splay_tree(splayNode* root);
void splay_tree_demo(void);

#endif // SPLAY_TREE_H
