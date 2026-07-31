#include "dynamic_programming.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 999999999

static int** allocate_dist(int n)
{
    int** dist = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        dist[i] = malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = 0;
        }
    }
    return dist;
}

static void free_dist(int** dist, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(dist[i]);
    }
    free(dist);
}

void test_tsp_n1()
{
    int n = 1;
    int** dist = allocate_dist(n);
    int* path = NULL;
    int cost = solve_tsp(n, dist, &path);

    assert(cost == 0);
    assert(path != NULL);
    assert(path[0] == 0 && path[1] == 0);

    free(path);
    free_dist(dist, n);
}

void test_tsp_n2()
{
    int n = 2;
    int** dist = allocate_dist(n);
    dist[0][1] = 10;
    dist[1][0] = 15;

    int* path = NULL;
    int cost = solve_tsp(n, dist, &path);

    assert(cost == 25);
    assert(path != NULL);
    assert(path[0] == 0 && path[1] == 1 && path[2] == 0);

    free(path);
    free_dist(dist, n);
}

void test_tsp_standard()
{
    int n = 4;
    int** dist = allocate_dist(n);
    int adj[4][4] = {{0, 10, 15, 20}, {10, 0, 35, 25}, {15, 35, 0, 30}, {20, 25, 30, 0}};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            dist[i][j] = adj[i][j];
        }
    }

    int* path = NULL;
    int cost = solve_tsp(n, dist, &path);

    assert(cost == 80);
    assert(path != NULL);

    free(path);
    free_dist(dist, n);
}

void test_tsp_unreachable()
{
    int n = 3;
    int** dist = allocate_dist(n);
    dist[0][1] = 10;
    dist[1][2] = 20;

    int* path = NULL;
    int cost = solve_tsp(n, dist, &path);

    assert(cost >= INF);
    assert(path == NULL);

    free(path);
    free_dist(dist, n);
}

void test_tsp_asymmetric()
{
    int n = 3;
    int** dist = allocate_dist(n);
    dist[0][1] = 1;
    dist[1][2] = 2;
    dist[2][0] = 10;
    dist[0][2] = 5;
    dist[2][1] = 5;
    dist[1][0] = 100;

    int* path = NULL;
    int cost = solve_tsp(n, dist, &path);

    assert(cost == 13);
    assert(path != NULL);

    free(path);
    free_dist(dist, n);
}

int main()
{
    test_tsp_n1();
    test_tsp_n2();
    test_tsp_standard();
    test_tsp_unreachable();
    test_tsp_asymmetric();

    fprintf(stdout, "All TSP DP tests passed successfully!\n");
    return 0;
}
