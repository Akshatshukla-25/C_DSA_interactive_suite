#ifndef DP_VISUALIZER_H
#define DP_VISUALIZER_H

#include <stdio.h>

// 1D DP table visualizer (e.g. for Fibonacci)
void visualize_dp_table_1d(const char* label, const long long* table, int size, int active_index);

// 2D DP table visualizer (e.g. for LCS, Knapsack)
void visualize_dp_table_2d(const char* label, int** table, int rows, int cols,
                           const char* row_labels, const char* col_labels, int active_row,
                           int active_col);

// MCM custom table visualizer (for m-table and s-table)
void visualize_mcm_tables(const int* m, const int* s, int n, int active_i, int active_j);

#endif // DP_VISUALIZER_H
