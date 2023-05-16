#include <stdio.h>
#define n 4

int g[n][n] = {
    {0, 1, 1, 1},
    {1, 0, 1, 1},
    {1, 1, 0, 1},
    {1, 1, 1, 0}};
int x[n] = {0, 0, 0, 0};
int m = 3;

void nextvalue(int k)
{
    while (1)
    {
        x[k] = (x[k] + 1) % (n);
        if (x[k] == 0)
            return;
        if (g[x[k - 1]][x[k]] != 0)
        {
            int j;
            for (j = 0; j < k; j++)
            {
                if (x[j] == x[k])
                    break;
            }
            if (j == k)
            {
                if ((k < n - 1) || (k == n - 1 && g[x[n - 1]][x[0]] != 0))
                    return;
            }
        }
    }
}

void hamiltonian(int k)
{
    while (1)
    {

        nextvalue(k);

        if (x[k] == 0)
            return;

        if (k == n - 1)
        {
            for (int i = 0; i < n; i++)
                printf("%d ", x[i] + 1);
            printf("\n");
        }
        else
            hamiltonian(k + 1);
    }
}

int main()
{
    x[0] = 0;
    hamiltonian(1);
}