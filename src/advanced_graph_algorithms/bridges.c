#include "advanced_graph_algorithms.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void bridge_dfs(Graph* graph, int u, int* disc, int* low, int* parent, int*** bridges,
                       int* bridge_count, int* time)
{
    disc[u] = low[u] = ++(*time);

    Node* temp = graph->array[u];
    while (temp != NULL)
    {
        int v = (int)(intptr_t)temp->data;

        if (disc[v] == -1)
        {
            parent[v] = u;
            bridge_dfs(graph, v, disc, low, parent, bridges, bridge_count, time);

            if (low[v] < low[u])
            {
                low[u] = low[v];
            }

            if (low[v] > disc[u])
            {
                (*bridge_count)++;
                int** new_bridges = realloc(*bridges, sizeof(int*) * (*bridge_count));
                if (new_bridges != NULL)
                {
                    *bridges = new_bridges;
                    (*bridges)[*bridge_count - 1] = malloc(sizeof(int) * 2);
                    (*bridges)[*bridge_count - 1][0] = u;
                    (*bridges)[*bridge_count - 1][1] = v;
                }
            }
        }
        else if (v != parent[u])
        {
            if (disc[v] < low[u])
            {
                low[u] = disc[v];
            }
        }
        temp = temp->next;
    }
}

int** find_bridges(Graph* graph, int* bridge_count)
{
    if (graph == NULL || bridge_count == NULL)
    {
        return NULL;
    }

    int V = graph->V;
    int* disc = malloc(sizeof(int) * V);
    int* low = malloc(sizeof(int) * V);
    int* parent = malloc(sizeof(int) * V);

    if (!disc || !low || !parent)
    {
        free(disc);
        free(low);
        free(parent);
        return NULL;
    }

    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
    }

    int time = 0;
    int** bridges = NULL;
    *bridge_count = 0;

    for (int i = 0; i < V; i++)
    {
        if (disc[i] == -1)
        {
            bridge_dfs(graph, i, disc, low, parent, &bridges, bridge_count, &time);
        }
    }

    free(disc);
    free(low);
    free(parent);

    return bridges;
}

void free_bridges(int** bridges, int count)
{
    if (bridges != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            if (bridges[i] != NULL)
            {
                free(bridges[i]);
            }
        }
        free(bridges);
    }
}
