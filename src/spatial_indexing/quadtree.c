#include "quadtree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool rect_contains(Rect b, double x, double y)
{
    return (x >= b.x - b.width && x <= b.x + b.width && y >= b.y - b.height && y <= b.y + b.height);
}

static bool rect_intersects(Rect a, Rect b)
{
    return !(a.x - a.width > b.x + b.width || a.x + a.width < b.x - b.width ||
             a.y - a.height > b.y + b.height || a.y + a.height < b.y - b.height);
}

static QuadTreeNode* create_quad_node(Rect boundary, size_t capacity)
{
    QuadTreeNode* node = (QuadTreeNode*)malloc(sizeof(QuadTreeNode));
    if (!node)
    {
        return NULL;
    }

    node->boundary = boundary;
    node->capacity = capacity;
    node->count = 0;
    node->divided = false;

    node->points = (QuadPoint*)malloc(sizeof(QuadPoint) * capacity);
    if (!node->points)
    {
        free(node);
        return NULL;
    }

    node->nw = NULL;
    node->ne = NULL;
    node->sw = NULL;
    node->se = NULL;

    return node;
}

QuadTree* quadtree_create(Rect boundary, size_t capacity)
{
    if (capacity == 0 || boundary.width <= 0 || boundary.height <= 0)
    {
        return NULL;
    }

    QuadTree* tree = (QuadTree*)malloc(sizeof(QuadTree));
    if (!tree)
    {
        return NULL;
    }

    tree->root = create_quad_node(boundary, capacity);
    if (!tree->root)
    {
        free(tree);
        return NULL;
    }

    tree->capacity = capacity;
    tree->total_points = 0;

    return tree;
}

static bool subdivide(QuadTreeNode* node)
{
    double x = node->boundary.x;
    double y = node->boundary.y;
    double w = node->boundary.width / 2.0;
    double h = node->boundary.height / 2.0;

    Rect nw_rect = {x - w, y + h, w, h};
    Rect ne_rect = {x + w, y + h, w, h};
    Rect sw_rect = {x - w, y - h, w, h};
    Rect se_rect = {x + w, y - h, w, h};

    node->nw = create_quad_node(nw_rect, node->capacity);
    node->ne = create_quad_node(ne_rect, node->capacity);
    node->sw = create_quad_node(sw_rect, node->capacity);
    node->se = create_quad_node(se_rect, node->capacity);

    /* Roll back all successful allocations if any child failed */
    if (!node->nw || !node->ne || !node->sw || !node->se)
    {
        free(node->nw);
        free(node->ne);
        free(node->sw);
        free(node->se);
        node->nw = NULL;
        node->ne = NULL;
        node->sw = NULL;
        node->se = NULL;
        return false;
    }

    node->divided = true;
    return true;
}

static bool node_insert(QuadTreeNode* node, double x, double y, void* data)
{
    if (!rect_contains(node->boundary, x, y))
    {
        return false;
    }

    if (node->count < node->capacity && !node->divided)
    {
        node->points[node->count].x = x;
        node->points[node->count].y = y;
        node->points[node->count].data = data;
        node->count++;
        return true;
    }

    if (!node->divided)
    {
        if (!subdivide(node))
        {
            return false; /* allocation failure: cannot subdivide */
        }
        /* Redistribute existing points */
        for (size_t i = 0; i < node->count; i++)
        {
            QuadPoint pt = node->points[i];
            bool redistributed = node_insert(node->nw, pt.x, pt.y, pt.data) ||
                                 node_insert(node->ne, pt.x, pt.y, pt.data) ||
                                 node_insert(node->sw, pt.x, pt.y, pt.data) ||
                                 node_insert(node->se, pt.x, pt.y, pt.data);
            (void)redistributed;
        }
        node->count = 0;
    }

    return (node_insert(node->nw, x, y, data) || node_insert(node->ne, x, y, data) ||
            node_insert(node->sw, x, y, data) || node_insert(node->se, x, y, data));
}

bool quadtree_insert(QuadTree* tree, double x, double y, void* data)
{
    if (!tree || !tree->root)
    {
        return false;
    }

    bool res = node_insert(tree->root, x, y, data);
    if (res)
    {
        tree->total_points++;
    }
    return res;
}

static void node_query_range(const QuadTreeNode* node, Rect range, QuadPoint** results,
                             size_t* capacity, size_t* count)
{
    if (!node || !rect_intersects(node->boundary, range))
    {
        return;
    }

    for (size_t i = 0; i < node->count; i++)
    {
        if (rect_contains(range, node->points[i].x, node->points[i].y))
        {
            if (*count >= *capacity)
            {
                size_t new_cap = (*capacity == 0) ? 16 : (*capacity * 2);
                QuadPoint* new_res = (QuadPoint*)realloc(*results, sizeof(QuadPoint) * new_cap);
                if (!new_res)
                {
                    return;
                }
                *results = new_res;
                *capacity = new_cap;
            }
            (*results)[*count] = node->points[i];
            (*count)++;
        }
    }

    if (node->divided)
    {
        node_query_range(node->nw, range, results, capacity, count);
        node_query_range(node->ne, range, results, capacity, count);
        node_query_range(node->sw, range, results, capacity, count);
        node_query_range(node->se, range, results, capacity, count);
    }
}

size_t quadtree_query_range(const QuadTree* tree, Rect range, QuadPoint** results)
{
    if (!tree || !tree->root || !results)
    {
        return 0;
    }

    *results = NULL;
    size_t capacity = 0;
    size_t count = 0;

    node_query_range(tree->root, range, results, &capacity, &count);

    return count;
}

static void free_quad_nodes(QuadTreeNode* node)
{
    if (!node)
    {
        return;
    }
    if (node->divided)
    {
        free_quad_nodes(node->nw);
        free_quad_nodes(node->ne);
        free_quad_nodes(node->sw);
        free_quad_nodes(node->se);
    }
    if (node->points)
    {
        free(node->points);
    }
    free(node);
}

void quadtree_free(QuadTree* tree)
{
    if (!tree)
    {
        return;
    }
    free_quad_nodes(tree->root);
    free(tree);
}
