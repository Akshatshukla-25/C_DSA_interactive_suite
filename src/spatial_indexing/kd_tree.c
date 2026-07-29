#include "kd_tree.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static double distance_sq(const double* p1, const double* p2, int k)
{
    double sum = 0.0;
    for (int i = 0; i < k; i++)
    {
        double diff = p1[i] - p2[i];
        sum += diff * diff;
    }
    return sum;
}

KDTree* kdtree_create(int k)
{
    if (k < 1)
    {
        return NULL;
    }

    KDTree* tree = (KDTree*)malloc(sizeof(KDTree));
    if (!tree)
    {
        return NULL;
    }

    tree->k = k;
    tree->count = 0;
    tree->root = NULL;

    return tree;
}

static KDNode* create_kd_node(const double* point, int k, int depth, void* data)
{
    KDNode* node = (KDNode*)malloc(sizeof(KDNode));
    if (!node)
    {
        return NULL;
    }

    node->point = (double*)malloc(sizeof(double) * k);
    if (!node->point)
    {
        free(node);
        return NULL;
    }

    memcpy(node->point, point, sizeof(double) * k);
    node->data = data;
    node->depth = depth;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static KDNode* insert_recursive(KDNode* node, const double* point, int k, int depth, void* data,
                                bool* success)
{
    if (node == NULL)
    {
        *success = true;
        return create_kd_node(point, k, depth, data);
    }

    int axis = depth % k;

    if (point[axis] < node->point[axis])
    {
        node->left = insert_recursive(node->left, point, k, depth + 1, data, success);
    }
    else
    {
        node->right = insert_recursive(node->right, point, k, depth + 1, data, success);
    }

    return node;
}

bool kdtree_insert(KDTree* tree, const double* point, void* data)
{
    if (!tree || !point)
    {
        return false;
    }

    bool success = false;
    tree->root = insert_recursive(tree->root, point, tree->k, 0, data, &success);
    if (success)
    {
        tree->count++;
    }
    return success;
}

static void range_search_recursive(const KDNode* node, const double* min_pt, const double* max_pt,
                                   int k, KDNode*** results, size_t* capacity, size_t* count)
{
    if (!node)
    {
        return;
    }

    /* Check if current node is inside hyper-rectangle */
    bool inside = true;
    for (int i = 0; i < k; i++)
    {
        if (node->point[i] < min_pt[i] || node->point[i] > max_pt[i])
        {
            inside = false;
            break;
        }
    }

    if (inside)
    {
        if (*count >= *capacity)
        {
            size_t new_cap = (*capacity == 0) ? 16 : (*capacity * 2);
            KDNode** new_res = (KDNode**)realloc(*results, sizeof(KDNode*) * new_cap);
            if (!new_res)
            {
                return;
            }
            *results = new_res;
            *capacity = new_cap;
        }
        (*results)[*count] = (KDNode*)node;
        (*count)++;
    }

    int axis = node->depth % k;

    if (min_pt[axis] <= node->point[axis])
    {
        range_search_recursive(node->left, min_pt, max_pt, k, results, capacity, count);
    }
    if (max_pt[axis] >= node->point[axis])
    {
        range_search_recursive(node->right, min_pt, max_pt, k, results, capacity, count);
    }
}

size_t kdtree_range_search(const KDTree* tree, const double* min_pt, const double* max_pt,
                           KDNode*** results)
{
    if (!tree || !min_pt || !max_pt || !results)
    {
        return 0;
    }

    *results = NULL;
    size_t capacity = 0;
    size_t count = 0;

    range_search_recursive(tree->root, min_pt, max_pt, tree->k, results, &capacity, &count);

    return count;
}

static void nn_search_recursive(const KDNode* node, const double* target, int k,
                                const KDNode** best_node, double* best_dist_sq)
{
    if (!node)
    {
        return;
    }

    double d_sq = distance_sq(node->point, target, k);
    if (d_sq < *best_dist_sq)
    {
        *best_dist_sq = d_sq;
        *best_node = node;
    }

    int axis = node->depth % k;
    double diff = target[axis] - node->point[axis];

    const KDNode* first = (diff < 0) ? node->left : node->right;
    const KDNode* second = (diff < 0) ? node->right : node->left;

    nn_search_recursive(first, target, k, best_node, best_dist_sq);

    /* Check if hypersphere crosses splitting hyperplane */
    if (diff * diff < *best_dist_sq)
    {
        nn_search_recursive(second, target, k, best_node, best_dist_sq);
    }
}

KDNode* kdtree_nearest_neighbor(const KDTree* tree, const double* target, double* best_dist)
{
    if (!tree || !tree->root || !target)
    {
        return NULL;
    }

    const KDNode* best_node = NULL;
    double best_dist_sq = DBL_MAX;

    nn_search_recursive(tree->root, target, tree->k, &best_node, &best_dist_sq);

    if (best_dist)
    {
        *best_dist = sqrt(best_dist_sq);
    }

    return (KDNode*)best_node;
}

static void free_nodes(KDNode* node)
{
    if (!node)
    {
        return;
    }
    free_nodes(node->left);
    free_nodes(node->right);
    if (node->point)
    {
        free(node->point);
    }
    free(node);
}

void kdtree_free(KDTree* tree)
{
    if (!tree)
    {
        return;
    }
    free_nodes(tree->root);
    free(tree);
}
