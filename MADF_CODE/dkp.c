#include <stdio.h>
#include <stdlib.h>
int max(int a, int b)
{
    return (a > b) ? a : b;
}

void knapsack(int n, int m, int w[], int p[])
{
    int v[n + 1][m + 1], x[n + 1];
    int i, j;
    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= m; j++)
        {
            if (i == 0 || j == 0)
                v[i][j] = 0;
            else if (w[i] > j)
                v[i][j] = v[i - 1][j];
            else
                v[i][j] = max(v[i - 1][j], v[i - 1][j - w[i]] + p[i]);
        }
    }
    printf("\nThe optimal solution is %d\n", v[n][m]);
    for (i = 0; i <= n; i++)
        x[i] = 0;
    i = n;
    j = m;
    while (i > 0 && j > 0)
    {
        if (v[i][j] != v[i - 1][j])
        {
            x[i] = 1;
            j = j - w[i];
        }
        i--;
    }
    printf("\n");
    for (i = 1; i <= n; i++)
    {
            printf("x[%d]= %d\n",i,x[i]);
    }
    printf("\n");
    printf("\nThe objects used are\n");
    for (i = 1; i <= n; i++)
    {
        if (x[i] == 1)
            printf("%d\t", i);
    }
    printf("\n");
}

int main()
{
    int n, m, i;
    printf("Enter the number of objects\n");
    scanf("%d", &n);
    int w[n + 1], p[n + 1];
    printf("Enter the weights of the objects\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    printf("Enter the profits of the objects\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    printf("Enter the capacity of the knapsack\n");
    scanf("%d", &m);
    knapsack(n, m, w, p);
    return 0;
}
