#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <stdbool.h>
#include <stddef.h>

// For Segment Tree (Dynamic Implementation)
typedef struct
{
    int* tree;
    int size;
    int original_array_size;
} SegmentTree;

SegmentTree* create_segment_tree(int arr[], int n);
void destroy_segment_tree(SegmentTree* st);
void build_tree(SegmentTree* st, int arr[], int node, int start, int end);
void update_point(SegmentTree* st, int node, int start, int end, int idx, int val);
int query_range(SegmentTree* st, int node, int start, int end, int l, int r);

void preorder_traversal(SegmentTree* st, int node, int start, int end);
void inorder_traversal(SegmentTree* st, int node, int start, int end);
void postorder_traversal(SegmentTree* st, int node, int start, int end);
void segment_tree_demo(void);

#endif // SEGMENT_TREE_H
