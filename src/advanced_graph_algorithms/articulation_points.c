#include "advanced_graph_algorithms.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void ap_dfs(Graph* graph, int u, int* disc, int* low, int* parent, bool* ap, int* time,
                   int* children)
{
    disc[u] = low[u] = ++(*time);

    Node* temp = graph->array[u];
    while (temp != NULL)
    {
        int v = (int)(intptr_t)temp->data;

        if (disc[v] == -1)
        {
            children[u]++;
            parent[v] = u;
            ap_dfs(graph, v, disc, low, parent, ap, time, children);

            if (low[v] < low[u])
            {
                low[u] = low[v];
            }

            // Condition for articulation point
            // (1) u is root of DFS tree and has two or more children.
            // (2) If u is not root and low value of one of its child is more
            //     than discovery value of u.
            if (parent[u] != -1 && low[v] >= disc[u])
            {
                ap[u] = true;
            }
        }
        else if (v != parent[u]) // Back edge
        {
            if (disc[v] < low[u])
            {
                low[u] = disc[v];
            }
        }
        temp = temp->next;
    }

    if (parent[u] == -1 && children[u] > 1)
    {
        ap[u] = true;
    }
}

bool* find_articulation_points(Graph* graph, int* count)
{
    if (graph == NULL || count == NULL)
    {
        return NULL;
    }

    int V = graph->V;
    int* disc = malloc(sizeof(int) * V);
    int* low = malloc(sizeof(int) * V);
    int* parent = malloc(sizeof(int) * V);
    bool* ap = malloc(sizeof(bool) * V);
    int* children = malloc(sizeof(int) * V);

    if (!disc || !low || !parent || !ap || !children)
    {
        free(disc);
        free(low);
        free(parent);
        free(ap);
        free(children);
        return NULL;
    }

    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        parent[i] = -1;
        ap[i] = false;
        children[i] = 0;
    }

    int time = 0;

    for (int i = 0; i < V; i++)
    {
        if (disc[i] == -1)
        {
            ap_dfs(graph, i, disc, low, parent, ap, &time, children);
        }
    }

    *count = 0;
    for (int i = 0; i < V; i++)
    {
        if (ap[i])
        {
            (*count)++;
        }
    }

    free(disc);
    free(low);
    free(parent);
    free(children);

    return ap;
}
