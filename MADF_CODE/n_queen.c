#include <stdio.h>
#include <stdlib.h>

int x[100];

int place(int k, int i)
{
    for (int j = 0; j < k; j++)
    {
        if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
            return 0;
    }
    return 1;
}

void nqueens(int k, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (place(k, i))
        {
            x[k] = i;
            if (k == n - 1)
            {
                for (int j = 0; j < n; j++)
                {
                    printf("%d ", x[j] + 1);
                }
                printf("\n");
                return;
            }
            else
                nqueens(k + 1, n);
        }
    }
}

int main()
{
    int n;
    printf("Enter the no of rows/columns: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        nqueens(i, n);
    }
}