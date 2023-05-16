#include <stdio.h>
#define n 4

int g[n][n] = {
    {0, 1, 1, 1},
    {1, 0, 1, 0},
    {1, 1, 0, 1},
    {1, 0, 1, 0}};
int x[n] = {0, 0, 0, 0};
int m = 3;

void nextvalue(int k)
{
    while (1)
    {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0)
        {
            return;
        }
        int j;
        for (j = 0; j < n; j++)
        {
            if (g[k][j] != 0 && x[k] == x[j])
                break;
        }
        if (j == n)
        {
            return;
        }
    }
}

void mcolouring(int k)
{
    while (1)
    {
        nextvalue(k);
        if (x[k] == 0)
            return;
        if (k == n - 1)
        {
            for (int i = 0; i < n; i++)
                printf("%d ", x[i]);
            printf("\n");
        }
        else
            mcolouring(k + 1);
    }
}

int main()
{
    mcolouring(0);
}