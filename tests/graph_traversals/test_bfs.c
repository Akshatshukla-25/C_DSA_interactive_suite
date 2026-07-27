#include "graph_traversals.h"
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mock_printf.h"

// Redirect printf to our mock
#define printf mock_printf
#include "../../src/graph_traversals/bfs.c"
#undef printf

void test_bfs_simple()
{
    reset_printf_buf();

    // Create a graph with 4 vertices
    Graph* graph = create_graph(4);
    assert(graph != NULL);

    // Add undirected edges: 0-1, 0-2, 1-3, 2-3
    add_edge_undirected(graph, 0, 1);
    add_edge_undirected(graph, 0, 2);
    add_edge_undirected(graph, 1, 3);
    add_edge_undirected(graph, 2, 3);

    bfs(graph, 0);

    // BFS order should print: 0->1->2->3->end
    assert(strstr(g_printf_buf, "0->1->2->3->end") != NULL);

    free_graph(graph);
}

void test_bfs_disconnected()
{
    reset_printf_buf();

    Graph* graph = create_graph(4);
    assert(graph != NULL);

    // Only add 0-1 edge, 2 and 3 are disconnected
    add_edge_undirected(graph, 0, 1);

    bfs(graph, 0);

    // BFS order starting from 0 should only traverse 0 and 1: 0->1->end
    assert(strstr(g_printf_buf, "0->1->end") != NULL);

    free_graph(graph);
}

void test_bfs_advanced_edge_cases()
{
    reset_printf_buf();

    /* NULL graph pointer guard */
    bfs(NULL, 0);

    /* Single vertex graph with no edges */
    Graph* graph_single = create_graph(1);
    assert(graph_single != NULL);
    bfs(graph_single, 0);
    assert(strstr(g_printf_buf, "0->end") != NULL);
    free_graph(graph_single);

    /* Graph with self-loop */
    reset_printf_buf();
    Graph* graph_loop = create_graph(2);
    assert(graph_loop != NULL);
    add_edge_undirected(graph_loop, 0, 0);
    add_edge_undirected(graph_loop, 0, 1);
    bfs(graph_loop, 0);
    assert(strstr(g_printf_buf, "0->1->end") != NULL);
    free_graph(graph_loop);

    /* Invalid start vertex index */
    reset_printf_buf();
    Graph* graph_inv = create_graph(3);
    assert(graph_inv != NULL);
    bfs(graph_inv, -1);
    bfs(graph_inv, 10);
    free_graph(graph_inv);

    printf("BFS advanced edge case tests passed\n");
}

int main()
{
    test_bfs_simple();
    test_bfs_disconnected();
    test_bfs_advanced_edge_cases();

    fprintf(stdout, "All BFS tests passed\n");
    return 0;
}
