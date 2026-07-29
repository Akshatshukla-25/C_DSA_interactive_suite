#ifndef KD_TREE_H
#define KD_TREE_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct KDNode
    {
        double* point;
        void* data;
        int depth;
        struct KDNode* left;
        struct KDNode* right;
    } KDNode;

    typedef struct KDTree
    {
        int k;        /* Dimension count (k >= 1) */
        size_t count; /* Total node count */
        KDNode* root;
    } KDTree;

    /**
     * @brief Create a new k-d Tree for k-dimensional points.
     * @param k Number of dimensions (k >= 1).
     * @return Pointer to initialized KDTree, or NULL on invalid args or failure.
     */
    KDTree* kdtree_create(int k);

    /**
     * @brief Insert a point with associated data payload into the k-d Tree.
     * @param tree Pointer to KDTree.
     * @param point Array of k coordinates.
     * @param data Optional pointer to associated data payload.
     * @return true on successful insertion, false on invalid args or error.
     */
    bool kdtree_insert(KDTree* tree, const double* point, void* data);

    /**
     * @brief Perform hyper-rectangle range search [min_pt, max_pt].
     * @param tree Pointer to KDTree.
     * @param min_pt Minimum bound coordinates (k dimensions).
     * @param max_pt Maximum bound coordinates (k dimensions).
     * @param results Pointer to store dynamically allocated array of matching KDNode pointers.
     * @return Number of matching nodes found. Caller must free(*results).
     */
    size_t kdtree_range_search(const KDTree* tree, const double* min_pt, const double* max_pt,
                               KDNode*** results);

    /**
     * @brief Find the Nearest Neighbor (1-NN) to a target query point.
     * @param tree Pointer to KDTree.
     * @param target Query point coordinates (k dimensions).
     * @param best_dist Optional pointer to store the Euclidean distance to nearest neighbor.
     * @return Pointer to nearest KDNode, or NULL if tree is empty.
     */
    KDNode* kdtree_nearest_neighbor(const KDTree* tree, const double* target, double* best_dist);

    /**
     * @brief Free all memory allocated for the k-d Tree.
     * @param tree Pointer to KDTree.
     */
    void kdtree_free(KDTree* tree);

#ifdef __cplusplus
}
#endif

#endif // KD_TREE_H
