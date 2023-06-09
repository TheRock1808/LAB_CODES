/*
Algorithm backward_graph(G,k,n,p)
{
    //the input is k-stage graph G=(V,E) of n vertices index of order of stages
    //E is set of edges and c[i,j] is the cost of edges <i,j>
    //p[i:k] is the minimun cost path
    bcost[1] := 0;
    for j := 2 to n do
    {
        let r be vertex such that <j,r> is an edge of G and c[j,r] + cost[r] is minimum
        cost[j] := c[j,r] + cost[r];
        dist[j] := r;
    }
    p[1] := 1;
    p[n] := k;
    for j := 2 to k-1 do
    p[j] := dist[p[j-1]];
}
*/
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

void bgraph(int C[][MAX], int n)
{
    int bcost[MAX], d[MAX], r, path[MAX], k;
    printf("Enter the number of stages: ");
    scanf("%d", &k);
    bcost[1] = 0;
    for (int j = 1; j <n; j++)
    {
        int mn = INT_MAX;
        for (r = j + 1; r <= n; r++)
        {
            if (C[j][r] && C[j][r] + bcost[r] < mn)
            {
                mn = C[j][r] + bcost[r];
                d[j] = r;
            }
        }
        bcost[j] = mn;
    }
    path[1] = 1;
    path[n] = k;
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
    bgraph(Graph, n);
}

/*
1 2 2
1 3 1
1 4 3
2 5 2
2 6 3
3 5 6 
3 6 7
4 5 6
4 6 8
4 7 9
5 8 6
6 8 4
7 8 5
*/