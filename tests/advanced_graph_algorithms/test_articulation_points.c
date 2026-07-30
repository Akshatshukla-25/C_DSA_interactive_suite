#include "advanced_graph_algorithms.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void test_articulation_points_dumbbell()
{
    Graph* g = create_graph(5);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 1, 2);
    add_edge_undirected(g, 2, 0);

    add_edge_undirected(g, 2, 3);
    add_edge_undirected(g, 3, 4);
    add_edge_undirected(g, 4, 2);

    int count = 0;
    bool* ap = find_articulation_points(g, &count);

    assert(ap != NULL);
    assert(count == 1);
    assert(ap[2] == true);
    assert(ap[0] == false);

    free(ap);
    free_graph(g);
}

void test_articulation_points_star()
{
    Graph* g = create_graph(4);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 0, 2);
    add_edge_undirected(g, 0, 3);

    int count = 0;
    bool* ap = find_articulation_points(g, &count);

    assert(ap != NULL);
    assert(count == 1);
    assert(ap[0] == true);
    assert(ap[1] == false);

    free(ap);
    free_graph(g);
}

void test_articulation_points_cycle()
{
    Graph* g = create_graph(4);
    add_edge_undirected(g, 0, 1);
    add_edge_undirected(g, 1, 2);
    add_edge_undirected(g, 2, 3);
    add_edge_undirected(g, 3, 0);

    int count = 0;
    bool* ap = find_articulation_points(g, &count);

    assert(ap != NULL);
    assert(count == 0);

    free(ap);
    free_graph(g);
}

int main()
{
    test_articulation_points_dumbbell();
    test_articulation_points_star();
    test_articulation_points_cycle();

    fprintf(stdout, "All Articulation Points tests passed successfully!\n");
    return 0;
}
