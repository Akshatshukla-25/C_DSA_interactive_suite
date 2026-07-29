#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Rect
    {
        double x;      /* Center X or Min X */
        double y;      /* Center Y or Min Y */
        double width;  /* Half-width or full width */
        double height; /* Half-height or full height */
    } Rect;

    typedef struct QuadPoint
    {
        double x;
        double y;
        void* data;
    } QuadPoint;

    typedef struct QuadTreeNode
    {
        Rect boundary;
        size_t capacity;
        QuadPoint* points;
        size_t count;
        bool divided;
        struct QuadTreeNode* nw;
        struct QuadTreeNode* ne;
        struct QuadTreeNode* sw;
        struct QuadTreeNode* se;
    } QuadTreeNode;

    typedef struct QuadTree
    {
        QuadTreeNode* root;
        size_t capacity;
        size_t total_points;
    } QuadTree;

    /**
     * @brief Create a 2D QuadTree spatial region index.
     * @param boundary Bounding box (center x, y, half-width, half-height).
     * @param capacity Maximum points per node before splitting.
     * @return Pointer to initialized QuadTree, or NULL on error.
     */
    QuadTree* quadtree_create(Rect boundary, size_t capacity);

    /**
     * @brief Insert a point into the QuadTree.
     * @param tree Pointer to QuadTree.
     * @param x X coordinate.
     * @param y Y coordinate.
     * @param data Optional payload data pointer.
     * @return true on success, false if point lies outside boundary or error.
     */
    bool quadtree_insert(QuadTree* tree, double x, double y, void* data);

    /**
     * @brief Perform 2D range query within a bounding box.
     * @param tree Pointer to QuadTree.
     * @param range Query range bounding box.
     * @param results Pointer to store dynamically allocated array of QuadPoint.
     * @return Number of matching points found. Caller must free(*results).
     */
    size_t quadtree_query_range(const QuadTree* tree, Rect range, QuadPoint** results);

    /**
     * @brief Free resources associated with a QuadTree.
     * @param tree Pointer to QuadTree.
     */
    void quadtree_free(QuadTree* tree);

#ifdef __cplusplus
}
#endif

#endif // QUADTREE_H
