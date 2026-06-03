#include "graph_traversals.h"
#include "safe_input.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int astar_solve(weightedGraph* graph, int start, int dest, int h[], int parent[])
{
    int size = graph->V;
    int* visited = calloc(size, sizeof(int));
    int* dist = malloc(size * sizeof(int));
    int* fScore = malloc(size * sizeof(int));

    if (!visited || !dist || !fScore)
    {
        free(visited);
        free(dist);
        free(fScore);
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        dist[i] = INT_MAX;
        fScore[i] = INT_MAX;
        if (parent)
        {
            parent[i] = -1;
        }
    }

    dist[start] = 0;
    fScore[start] = h[start];

    while (1)
    {
        int minDist = INT_MAX;
        int u = -1;
        for (int i = 0; i < size; i++)
        {
            if (!visited[i] && fScore[i] < minDist)
            {
                minDist = fScore[i];
                u = i;
            }
        }

        if (u == -1)
        {
            break;
        }

        visited[u] = 1;

        if (u == dest)
        {
            break;
        }

        Edge* current = graph->array[u];
        while (current != NULL)
        {
            int v = current->destination;
            int currentWeight = current->weight;

            if (!visited[v] && dist[u] != INT_MAX)
            {
                int tentative_g = dist[u] + currentWeight;
                if (tentative_g < dist[v])
                {
                    dist[v] = tentative_g;
                    if (parent)
                    {
                        parent[v] = u;
                    }

                    int tentative_f = tentative_g + h[v];
                    if (tentative_f < 0)
                    {
                        tentative_f = INT_MAX;
                    }
                    fScore[v] = tentative_f;
                }
            }
            current = current->next;
        }
    }

    int result = dist[dest];
    free(visited);
    free(dist);
    free(fScore);
    return result;
}

void astar(weightedGraph* graph, int start, int dest, int h[])
{
    int size = graph->V;
    int* parent = malloc(size * sizeof(int));
    if (!parent)
    {
        printf("Memory allocation failed in A*\n");
        return;
    }

    int cost = astar_solve(graph, start, dest, h, parent);

    if (cost == INT_MAX || cost < 0)
    {
        printf("No path exists from %d to %d\n", start, dest);
    }
    else
    {
        int* path = malloc(size * sizeof(int));
        if (!path)
        {
            printf("Memory allocation failed in A*\n");
            free(parent);
            return;
        }
        int pathLen = 0;
        int curr = dest;
        while (curr != -1)
        {
            path[pathLen++] = curr;
            curr = parent[curr];
        }

        printf("Shortest Path: ");
        for (int i = pathLen - 1; i >= 0; i--)
        {
            printf("%d", path[i]);
            if (i > 0)
            {
                printf(" -> ");
            }
        }
        printf("\nTotal Cost: %d\n", cost);
        free(path);
    }
    free(parent);
}

void astar_demo(void)
{
    int edges;
    int graph_capacity;
    int starting_node;
    int destination_node;
    weightedGraph* graph = NULL;
    int* h = NULL;

    while (1)
    {
        int graph_capacity_status = safe_input_int(&graph_capacity,
                                                   "\nenter the number of vertices in the graph, "
                                                   "(between 1 and 10), enter '-1' to exit : ",
                                                   1, 10);

        if (graph_capacity_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo.....\n");
            return;
        }

        if (graph_capacity_status == 0)
        {
            continue;
        }

        graph = create_weightedGraph(graph_capacity);

        if (!graph)
        {
            printf("\nmemory allocation failed\n");
            return;
        }

        break;
    }

    while (1)
    {
        int edges_capacity_status = safe_input_int(
            &edges, "\nenter number of edges (between 1 and 100), enter '-1' to exit :", 0, 100);

        if (edges_capacity_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo\n");
            free_weightedGraph(graph);
            return;
        }

        if (edges_capacity_status == 0)
        {
            continue;
        }

        break;
    }

    printf("\nEnter source, destination, weight pairs (Source, Destination must be b/w 0 and %d "
           "(both inclusive)):\n",
           graph_capacity - 1);

    for (int i = 0; i < edges; i++)
    {
        int src_status;
        int dest_status;
        int wt_status;
        int src;
        int dest;
        int wt;

    retry:
        src_status = safe_input_int(&src, "src: ", 0, graph_capacity - 1);

        if (src_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo\n");
            free_weightedGraph(graph);
            return;
        }
        if (src_status == 0)
        {
            goto retry;
        }

        dest_status = safe_input_int(&dest, "dest: ", 0, graph_capacity - 1);

        if (dest_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo\n");
            free_weightedGraph(graph);
            return;
        }
        if (dest_status == 0)
        {
            goto retry;
        }

        wt_status = safe_input_int(&wt, "weight: ", 0, INT_MAX);

        if (wt_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo\n");
            free_weightedGraph(graph);
            return;
        }
        if (wt_status == 0)
        {
            goto retry;
        }

        add_edge_directed(graph, src, dest, wt);
    }

    h = malloc(graph_capacity * sizeof(int));
    if (!h)
    {
        printf("\nmemory allocation failed for heuristics\n");
        free_weightedGraph(graph);
        return;
    }

    printf("\nEnter heuristic values for each vertex:\n");
    for (int i = 0; i < graph_capacity; i++)
    {
        int h_val;
        int h_status;
        char prompt[50];
        sprintf(prompt, "h(%d): ", i);
    retry_h:
        h_status = safe_input_int(&h_val, prompt, 0, INT_MAX);
        if (h_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo\n");
            free(h);
            free_weightedGraph(graph);
            return;
        }
        if (h_status == 0)
        {
            goto retry_h;
        }
        h[i] = h_val;
    }

    while (1)
    {
        int start_status =
            safe_input_int(&starting_node, "\nenter starting node: ", 0, graph_capacity - 1);

        if (start_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo.....\n");
            free(h);
            free_weightedGraph(graph);
            return;
        }

        if (start_status == 0)
        {
            continue;
        }

        break;
    }

    while (1)
    {
        int dest_status =
            safe_input_int(&destination_node, "\nenter destination node: ", 0, graph_capacity - 1);

        if (dest_status == INPUT_EXIT_SIGNAL)
        {
            printf("\nExiting A* demo.....\n");
            free(h);
            free_weightedGraph(graph);
            return;
        }

        if (dest_status == 0)
        {
            continue;
        }

        break;
    }

    printf("\n");
    astar(graph, starting_node, destination_node, h);
    free(h);
    free_weightedGraph(graph);
}
