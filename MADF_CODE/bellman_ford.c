#include <stdio.h>
#include <limits.h>
#define N 50
#define inf 99999

void fillinf(int a[][N], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = inf;
}

void getmat(int a[][N], int n)
{
    int w, x, y;
    for (int i = 0; i < n * (n - 1); i++)
    {
        scanf("%d", &x);
        scanf("%d", &y);
        if (x == -1 && y == -1)
            return;
        scanf("%d", &w);
        a[--x][--y] = w;
    }
}

int _min(int a, int b)
{
    return a < b ? a : b;
}

void showmat(int a[N], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == inf)
            printf("inf\t");
        else
            printf("%d\t", a[i]);
    }
}

int incoming(int u, int a[][N], int v)
{
    for (int i = 0; i < v; i++)
        if (a[i][u] != inf)
            return 1;
    return 0;
}

void show2dmat(int a[][N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i][j] == inf)
                printf("inf ");
            else
                printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void bellman(int src, int cost[][N], int v)
{
    int dist[N];
    for (int i = 0; i < v; i++)
        dist[i] = cost[src][i];
    dist[src] = 0;
    printf("k = 1: ");
    showmat(dist, v);
    printf("\n");
    for (int k = 2; k <= v - 1; k++)
    {
        for (int u = 0; u < v; u++)
        {
            if (u != src && incoming(u, cost, v) == 1)
            {
                for (int i = 0; i < v; i++)
                {
                    if (cost[i][u] != inf)
                    {
                        if (dist[u] > dist[i] + cost[i][u])
                            dist[u] = dist[i] + cost[i][u];
                    }
                }
            }
        }
        printf("k = %d: ", k);
        showmat(dist, v);
        printf("\n");
    }
}

int main()
{
    int n, a[N][N], source;
    printf("Enter the number of vertices - ");
    scanf("%d", &n);
    fillinf(a, n);
    printf("Enter the weights as u v w(enter -1 -1 to to stop taking input)\n");
    getmat(a, n);
    printf("Enter the source vertex - ");
    scanf("%d", &source);
    bellman(--source, a, n);
    return 0;
}

/*
7
1 2 4
1 4 5
2 3 2
2 4 6
3 5 -4
3 7 -4
4 5 -1
4 6 -3
5 6 -2
5 7 -1
6 7 3
-1 -1
1
*/