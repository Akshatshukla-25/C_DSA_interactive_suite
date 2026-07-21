#include "fuzzer.h"
#include "graph_traversals.h"
#include "step_debugger.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void run_unweighted_graph_fuzz(FuzzerState* fuzzer, int num_nodes, int num_edges)
{
    Graph* graph = create_graph(num_nodes);
    assert(graph != NULL);

    for (int i = 0; i < num_edges; i++)
    {
        int u = fuzzer_rand_int(fuzzer, 0, num_nodes - 1);
        int v = fuzzer_rand_int(fuzzer, 0, num_nodes - 1);
        int dir = fuzzer_rand_int(fuzzer, 0, 1);
        if (dir == 0)
        {
            fuzzer_log_op(fuzzer, "Add undirected edge %d-%d", u, v);
            add_edge_undirected(graph, u, v);
        }
        else
        {
            fuzzer_log_op(fuzzer, "Add directed edge %d->%d", u, v);
            add_edge_directed_unweighted(graph, u, v);
        }
    }

    int start = fuzzer_rand_int(fuzzer, 0, num_nodes - 1);
    fuzzer_log_op(fuzzer, "BFS traversal from %d", start);
    bfs(graph, start);

    fuzzer_log_op(fuzzer, "DFS traversal from %d", start);
    dfs(graph, start);

    fuzzer_log_op(fuzzer, "Topological sort Kahn");
    topological_sort_kahn(graph);

    free_graph(graph);
}

void run_weighted_graph_fuzz(FuzzerState* fuzzer, int num_nodes, int num_edges)
{
    weightedGraph* graph = create_weightedGraph(num_nodes);
    assert(graph != NULL);

    for (int i = 0; i < num_edges; i++)
    {
        int u = fuzzer_rand_int(fuzzer, 0, num_nodes - 1);
        int v = fuzzer_rand_int(fuzzer, 0, num_nodes - 1);
        int w = fuzzer_rand_int(fuzzer, 1, 100);
        fuzzer_log_op(fuzzer, "Add weighted edge %d->%d weight %d", u, v, w);
        add_edge_directed(graph, u, v, w);
    }

    int start = fuzzer_rand_int(fuzzer, 0, num_nodes - 1);
    fuzzer_log_op(fuzzer, "Dijkstra from %d", start);
    dijkstra(graph, start);

    fuzzer_log_op(fuzzer, "Bellman-Ford from %d", start);
    bellman_ford(graph, start);

    fuzzer_log_op(fuzzer, "Kruskal MST");
    kruskal_mst(graph);

    fuzzer_log_op(fuzzer, "Prim MST from %d", start);
    prim_mst(graph, start);

    free_weightedGraph(graph);
}

int main(void)
{
    setenv("DSA_TEST_MODE", "1", 1);
    set_step_mode(0);
    set_paused(0);
    unsigned int seed = (unsigned int)time(NULL);
    FuzzerState fuzzer;
    printf("Starting Graph Fuzzing with seed: %u\n", seed);

    fuzzer_init(&fuzzer, seed, 5000);
    run_unweighted_graph_fuzz(&fuzzer, 30, 80);
    run_weighted_graph_fuzz(&fuzzer, 30, 80);
    fuzzer_free(&fuzzer);

    printf("Graph Fuzzing completed successfully!\n");
    return 0;
}
