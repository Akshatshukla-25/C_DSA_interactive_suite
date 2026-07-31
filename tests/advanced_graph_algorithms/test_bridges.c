#include "advanced_graph_algorithms.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_bridges_dumbbell()
{
    Graph* g = create_graph(6);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 1, 2);
    add_edge_undirected(g, 2, 0);

    // The single bridge edge
    add_edge_undirected(g, 2, 3);

    add_edge_undirected(g, 3, 4);
    add_edge_undirected(g, 4, 5);
    add_edge_undirected(g, 5, 3);

    int count = 0;
    int** bridges = find_bridges(g, &count);

    assert(bridges != NULL);
    assert(count == 1);

    // The bridge edge should be between 2 and 3. The DFS may store it as [2,3] or [3,2].
    assert((bridges[0][0] == 2 && bridges[0][1] == 3) ||
           (bridges[0][0] == 3 && bridges[0][1] == 2));

    free_bridges(bridges, count);
    free_graph(g);
}

void test_bridges_cycle()
{
    Graph* g = create_graph(4);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 1, 2);
    add_edge_undirected(g, 2, 3);
    add_edge_undirected(g, 3, 0);

    int count = 0;
    int** bridges = find_bridges(g, &count);

    assert(bridges == NULL || count == 0);

    free_bridges(bridges, count);
    free_graph(g);
}

void test_bridges_tree()
{
    Graph* g = create_graph(4);
    // Tree topology: 0 is connected to 1, 2, 3 (a star graph)
    // Every edge in a tree is a bridge!
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 0, 2);
    add_edge_undirected(g, 0, 3);

    int count = 0;
    int** bridges = find_bridges(g, &count);

    assert(bridges != NULL);
    assert(count == 3);

    free_bridges(bridges, count);
    free_graph(g);
}

int main()
{
    test_bridges_dumbbell();
    test_bridges_cycle();
    test_bridges_tree();

    fprintf(stdout, "All Bridges tests passed successfully!\n");
    return 0;
}
