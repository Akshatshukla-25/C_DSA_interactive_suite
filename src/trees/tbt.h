#ifndef TBT_H
#define TBT_H

#include <stdbool.h>
#include <stddef.h>

// For Threaded Binary Tree
typedef struct TBTnode
{
    int data;
    bool lthread;
    bool rthread;
    struct TBTnode* left;
    struct TBTnode* right;
} TBTnode;

TBTnode* leftmost(TBTnode* node);
TBTnode* create_node_tbt(int data);
void preorder_tbt(TBTnode* node);
void inorder_tbt(TBTnode* node);
int insert_node_tbt(TBTnode** root_ref, int key);
void destroy_tbt(TBTnode* node);
void TBT_demo(void);

#endif // TBT_H
