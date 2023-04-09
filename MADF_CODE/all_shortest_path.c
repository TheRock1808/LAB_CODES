/*All pair shortest path*/

#include <stdio.h>
#include <limits.h>

const int V = 4;

int a[3][3] = {
    {0, 4, 11},
    {6, 0, 2},
    {3, INT_MAX, 0}
    };

int b[4][4] = {
    {0, 5, INT_MAX, 1},
    {4, 0, 8, 3},
    {INT_MAX, 7, 0, 5},
    {2, 4, 2, 0}
    };

void print(int n, int arr[n][n])
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (arr[i][j] == INT_MAX)
                printf("* ");
            else
                printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("-------------\n");
}

int min(int a, int b)
{
    return (a < b ? a : b);
}

void Allpair(int n, int cost[n][n])
{
    int A[n][n], i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i][j] = cost[i][j];

    printf("A0 = \n");
    print(n, A);
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (A[i][k] != INT_MAX && A[k][j] != INT_MAX)
                    A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
        printf("A%d = \n", k + 1);
        print(n, A);
    }
}

int main()
{
    Allpair(V, V == 3 ? a : b);
}