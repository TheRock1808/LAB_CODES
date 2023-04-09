#include <stdio.h>
#define INFINITY 999999
#define MAX 100

void shortest_path(int Graph[MAX][MAX], int n, int start);

void shortest_path(int Graph[MAX][MAX], int n, int start)
{
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode, i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (Graph[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = Graph[i][j];

    for (i = 0; i < n; i++)
    {
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while (count < n - 1)
    {
        mindistance = INFINITY;

        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }

        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    // Printing the distance
    for (i = 0; i < n; i++)
        if (i != start)
        {
            printf("\nDistance from source to %d: %d", i, distance[i]);
        }
}
int main()
{
    int i, j, n, u;
    n = 6;
    int Graph[MAX][MAX]={
        {0,10,5,20,10,0},
        {0,0,3,8,7,0},
        {0,5,0,6,3,0},
        {0,0,0,0,5,5},
        {0,0,0,2,0,3},
        {0,0,0,0,0,0}
    };
    u = 0;
    shortest_path(Graph, n, u);

    return 0;
}