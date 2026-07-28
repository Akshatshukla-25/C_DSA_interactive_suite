#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <stdbool.h>
#include <stddef.h>

// For Fenwick Tree (Binary Indexed Tree)
typedef struct
{
    int* BIT1;
    int* BIT2;
    int size;
} FenwickTree;

FenwickTree* create_fenwick_tree(int size);
void destroy_fenwick_tree(FenwickTree* ft);
void fenwick_point_update(int* BIT, int n, int idx, int delta);
void fenwick_range_update(FenwickTree* ft, int l, int r, int delta);
int fenwick_point_query(int* BIT, int idx);
int fenwick_range_query(FenwickTree* ft, int l, int r);
void fenwick_tree_demo(void);

#endif // FENWICK_TREE_H
