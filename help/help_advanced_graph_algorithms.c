#include "display_header.h"
#include "help.h"
#include "safe_input.h"
#include <stdio.h>

void help_advanced_graph_algorithms_menu(void)
{
    display_header("Help: Advanced Graph Algorithms & Network Resilience");

    printf("--- NETWORK FLOW & BIPARTITE MATCHING ---\n\n");
    printf("1. FORD-FULKERSON & EDMONDS-KARP MAX FLOW\n");
    printf("CONCEPT:\n");
    printf("   Computes maximum network flow from source node (s) to sink node (t)\n"
           "   in a weighted directed graph with capacity constraints.\n\n");
    printf("COMPLEXITY CHEAT TABLE:\n");
    printf("   +-----------------------+------------------------+-------------------+\n");
    printf("   | Algorithm             | Time Complexity        | Space Complexity  |\n");
    printf("   +-----------------------+------------------------+-------------------+\n");
    printf("   | Ford-Fulkerson (DFS)  | O(E * |f_max|)         | O(V + E)          |\n");
    printf("   | Edmonds-Karp (BFS)    | O(V * E^2)             | O(V + E)          |\n");
    printf("   | Dinic's Algorithm     | O(V^2 * E)             | O(V + E)          |\n");
    printf("   +-----------------------+------------------------+-------------------+\n\n");
    printf("2. BIPARTITE MATCHING (Dinic & Hopcroft-Karp)\n");
    printf("CONCEPT:\n");
    printf("   Finds maximum cardinality set of edges without common vertices in\n"
           "   bipartite graphs.\n");
    printf("   - Hopcroft-Karp Time Complexity: O(E * sqrt(V))\n");
    printf("   - Dinic Bipartite Time Complexity: O(E * sqrt(V))\n\n");

    printf("--- BRIDGES, ARTICULATION POINTS & NETWORK VULNERABILITY ---\n\n");
    printf("1. ARTICULATION POINTS (Cut Vertices)\n");
    printf("CONCEPT:\n");
    printf("   A vertex v is an articulation point if removing v increases the number\n"
           "   of connected components in the graph. Identified using DFS discovery\n"
           "   times and lowlink values.\n");
    printf("   - Condition: tin[u] <= low[v] for non-root, or child_count >= 2 for\n"
           "     root node.\n");
    printf("   - Time Complexity: O(V + E)\n");
    printf("   - Space Complexity: O(V)\n\n");
    printf("2. BRIDGES (Critical Edges)\n");
    printf("CONCEPT:\n");
    printf("   An edge (u, v) is a bridge if removing it disconnects the graph.\n");
    printf("   - Condition: tin[u] < low[v].\n");
    printf("   - Time Complexity: O(V + E)\n");
    printf("   - Space Complexity: O(V + E)\n\n");

    printf("\nPress [ENTER] to return...\n");
    press_enter_to_continue();
}
