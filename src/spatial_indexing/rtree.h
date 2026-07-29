#ifndef RTREE_H
#define RTREE_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct MBR
    {
        double min_x;
        double min_y;
        double max_x;
        double max_y;
    } MBR;

    typedef struct RTreeItem
    {
        MBR mbr;
        void* data;
    } RTreeItem;

    typedef struct RTreeNode
    {
        bool is_leaf;
        size_t count;
        MBR mbr;
        RTreeItem* items;
        struct RTreeNode** children;
    } RTreeNode;

    typedef struct RTree
    {
        RTreeNode* root;
        size_t max_entries;
        size_t min_entries;
        size_t total_items;
    } RTree;

    /**
     * @brief Initialize an R-Tree spatial bounding box index.
     * @param max_entries Maximum entries per node before split (M >= 2).
     * @param min_entries Minimum entries per node (m <= M / 2).
     * @return Pointer to initialized RTree, or NULL on error.
     */
    RTree* rtree_create(size_t max_entries, size_t min_entries);

    /**
     * @brief Insert a bounding box with data payload into the R-Tree.
     * @param tree Pointer to RTree.
     * @param mbr Minimum Bounding Rectangle.
     * @param data Optional payload pointer.
     * @return true on success, false on invalid args or error.
     */
    bool rtree_insert(RTree* tree, MBR mbr, void* data);

    /**
     * @brief Search for spatial bounding boxes intersecting query MBR.
     * @param tree Pointer to RTree.
     * @param search_mbr Bounding box query.
     * @param results Pointer to store dynamically allocated array of matching RTreeItem.
     * @return Number of matching items found. Caller must free(*results).
     */
    size_t rtree_search_mbr(const RTree* tree, MBR search_mbr, RTreeItem** results);

    /**
     * @brief Free resources associated with an R-Tree.
     * @param tree Pointer to RTree.
     */
    void rtree_free(RTree* tree);

    MBR mbr_combine(MBR a, MBR b);
    bool mbr_intersects(MBR a, MBR b);

#ifdef __cplusplus
}
#endif

#endif // RTREE_H
