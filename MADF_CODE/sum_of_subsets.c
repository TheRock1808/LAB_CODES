#include <stdio.h>

int n;

int w[100];
int x[100];
int m;

//{7,11,13,24} 31;

void sum_of_subsets(int s, int k, int r)
{
    x[k] = 1;

    if (s + w[k] == m)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d ", x[i]);
        }
        printf("\n");
        return;
    }
    else if (k + 1 < n && (s + w[k] + w[k + 1] <= m))
    {
        sum_of_subsets(s + w[k], k + 1, r - w[k]);
    }
    if (k + 1 < n && (s + r - w[k] >= m) && (s + w[k + 1] <= m))
    {
        x[k] = 0;
        sum_of_subsets(s, k + 1, r - w[k]);
    }
}

int main()
{
    int s = 0, k = 0, r = 0;
    printf("Enter the no of elemets in the set: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
    }
    printf("Enter the required sum: ");
    scanf("%d", &m);
    for (int i = 0; i < n; i++)
    {
        r += w[i];
    sum_of_subsets(s, k, r);
    }
}