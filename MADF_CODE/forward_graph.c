#include <stdio.h>
#include <limits.h>
#define MAX 100

void inputgraph(int Graph[][MAX], int n, int m)
{
    printf("Enter the edges and weights:\n");
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        Graph[u][v] = w;
    }
}

void fgraph(int C[][MAX], int n)
{
    int cost[MAX];
    int d[MAX], r, path[MAX], k;
    printf("enter the number of stages: ");
    scanf("%d", &k);
    cost[n] = 0;
    for (int j = n - 1; j >= 1; j--)
    {
        int mn = INT_MAX;
        for (r = j + 1; r <= n; r++)
        {
            if (C[j][r] && C[j][r] + cost[r] < mn)
            {
                mn = C[j][r] + cost[r];
                d[j] = k;
            }
        }
        cost[j] = mn;
    }
    path[1] = 1;
    path[k] = n;
    for (int i = 2; i < k; i++)
        path[i] = d[path[i - 1]];

    for (int i = 1; i <= k; i++)
        printf("%d ", path[i]);
}
int main()
{
    int i, j, n, m;
    int Graph[MAX][MAX];
    printf("Enter number of vertices and edges:\n");
    scanf("%d%d", &n, &m);
    inputgraph(Graph, n, m);
    fgraph(Graph, n);
}