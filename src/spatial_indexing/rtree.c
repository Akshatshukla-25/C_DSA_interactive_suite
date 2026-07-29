#include "rtree.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MBR mbr_combine(MBR a, MBR b)
{
    MBR res;
    res.min_x = (a.min_x < b.min_x) ? a.min_x : b.min_x;
    res.min_y = (a.min_y < b.min_y) ? a.min_y : b.min_y;
    res.max_x = (a.max_x > b.max_x) ? a.max_x : b.max_x;
    res.max_y = (a.max_y > b.max_y) ? a.max_y : b.max_y;
    return res;
}

bool mbr_intersects(MBR a, MBR b)
{
    return !(a.min_x > b.max_x || a.max_x < b.min_x || a.min_y > b.max_y || a.max_y < b.min_y);
}

static double mbr_area(MBR mbr)
{
    double w = mbr.max_x - mbr.min_x;
    double h = mbr.max_y - mbr.min_y;
    if (w < 0 || h < 0)
    {
        return 0.0;
    }
    return w * h;
}

static RTreeNode* create_rtree_node(bool is_leaf, size_t max_entries)
{
    RTreeNode* node = (RTreeNode*)malloc(sizeof(RTreeNode));
    if (!node)
    {
        return NULL;
    }

    node->is_leaf = is_leaf;
    node->count = 0;
    node->mbr = (MBR){DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX};

    if (is_leaf)
    {
        node->items = (RTreeItem*)malloc(sizeof(RTreeItem) * (max_entries + 1));
        node->children = NULL;
    }
    else
    {
        node->items = NULL;
        node->children = (RTreeNode**)malloc(sizeof(RTreeNode*) * (max_entries + 1));
    }

    return node;
}

RTree* rtree_create(size_t max_entries, size_t min_entries)
{
    if (max_entries < 2 || min_entries > max_entries / 2)
    {
        return NULL;
    }

    RTree* tree = (RTree*)malloc(sizeof(RTree));
    if (!tree)
    {
        return NULL;
    }

    tree->max_entries = max_entries;
    tree->min_entries = min_entries;
    tree->total_items = 0;

    tree->root = create_rtree_node(true, max_entries);
    if (!tree->root)
    {
        free(tree);
        return NULL;
    }

    return tree;
}

static void update_node_mbr(RTreeNode* node)
{
    if (node->count == 0)
    {
        node->mbr = (MBR){DBL_MAX, DBL_MAX, -DBL_MAX, -DBL_MAX};
        return;
    }

    if (node->is_leaf)
    {
        node->mbr = node->items[0].mbr;
        for (size_t i = 1; i < node->count; i++)
        {
            node->mbr = mbr_combine(node->mbr, node->items[i].mbr);
        }
    }
    else
    {
        node->mbr = node->children[0]->mbr;
        for (size_t i = 1; i < node->count; i++)
        {
            node->mbr = mbr_combine(node->mbr, node->children[i]->mbr);
        }
    }
}

static RTreeNode* split_node(RTree* tree, RTreeNode* node)
{
    RTreeNode* new_node = create_rtree_node(node->is_leaf, tree->max_entries);
    if (!new_node)
    {
        return NULL;
    }

    size_t half = node->count / 2;
    if (node->is_leaf)
    {
        for (size_t i = half; i < node->count; i++)
        {
            new_node->items[new_node->count++] = node->items[i];
        }
        node->count = half;
    }
    else
    {
        for (size_t i = half; i < node->count; i++)
        {
            new_node->children[new_node->count++] = node->children[i];
        }
        node->count = half;
    }

    update_node_mbr(node);
    update_node_mbr(new_node);

    return new_node;
}

static RTreeNode* insert_recursive(RTree* tree, RTreeNode* node, RTreeItem item)
{
    if (node->is_leaf)
    {
        node->items[node->count++] = item;
        update_node_mbr(node);

        if (node->count > tree->max_entries)
        {
            return split_node(tree, node);
        }
        return NULL;
    }

    /* Choose child with minimal MBR enlargement */
    size_t best_idx = 0;
    double min_enlargement = DBL_MAX;

    for (size_t i = 0; i < node->count; i++)
    {
        MBR combined = mbr_combine(node->children[i]->mbr, item.mbr);
        double enlargement = mbr_area(combined) - mbr_area(node->children[i]->mbr);
        if (enlargement < min_enlargement)
        {
            min_enlargement = enlargement;
            best_idx = i;
        }
    }

    RTreeNode* split_child = insert_recursive(tree, node->children[best_idx], item);
    update_node_mbr(node);

    if (split_child)
    {
        node->children[node->count++] = split_child;
        update_node_mbr(node);
        if (node->count > tree->max_entries)
        {
            return split_node(tree, node);
        }
    }

    return NULL;
}

bool rtree_insert(RTree* tree, MBR mbr, void* data)
{
    if (!tree || !tree->root)
    {
        return false;
    }

    RTreeItem item = {mbr, data};
    RTreeNode* split_root = insert_recursive(tree, tree->root, item);

    if (split_root)
    {
        RTreeNode* new_root = create_rtree_node(false, tree->max_entries);
        if (!new_root)
        {
            return false;
        }
        new_root->children[0] = tree->root;
        new_root->children[1] = split_root;
        new_root->count = 2;
        update_node_mbr(new_root);
        tree->root = new_root;
    }

    tree->total_items++;
    return true;
}

static void search_recursive(const RTreeNode* node, MBR search_mbr, RTreeItem** results,
                             size_t* capacity, size_t* count)
{
    if (!node || !mbr_intersects(node->mbr, search_mbr))
    {
        return;
    }

    if (node->is_leaf)
    {
        for (size_t i = 0; i < node->count; i++)
        {
            if (mbr_intersects(node->items[i].mbr, search_mbr))
            {
                if (*count >= *capacity)
                {
                    size_t new_cap = (*capacity == 0) ? 16 : (*capacity * 2);
                    RTreeItem* new_res = (RTreeItem*)realloc(*results, sizeof(RTreeItem) * new_cap);
                    if (!new_res)
                    {
                        return;
                    }
                    *results = new_res;
                    *capacity = new_cap;
                }
                (*results)[*count] = node->items[i];
                (*count)++;
            }
        }
    }
    else
    {
        for (size_t i = 0; i < node->count; i++)
        {
            search_recursive(node->children[i], search_mbr, results, capacity, count);
        }
    }
}

size_t rtree_search_mbr(const RTree* tree, MBR search_mbr, RTreeItem** results)
{
    if (!tree || !tree->root || !results)
    {
        return 0;
    }

    *results = NULL;
    size_t capacity = 0;
    size_t count = 0;

    search_recursive(tree->root, search_mbr, results, &capacity, &count);

    return count;
}

static void free_rtree_nodes(RTreeNode* node)
{
    if (!node)
    {
        return;
    }
    if (!node->is_leaf && node->children)
    {
        for (size_t i = 0; i < node->count; i++)
        {
            free_rtree_nodes(node->children[i]);
        }
        free(node->children);
    }
    if (node->is_leaf && node->items)
    {
        free(node->items);
    }
    free(node);
}

void rtree_free(RTree* tree)
{
    if (!tree)
    {
        return;
    }
    free_rtree_nodes(tree->root);
    free(tree);
}
