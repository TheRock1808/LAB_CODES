#include <stdio.h>

int a[10] = {55, 11, 33, 23, -17, 89, -11, 72, 43};
void minmax(int i, int j, int *max, int *min)
{
    if (i == j)
        *max = *min = a[i];
    else if (i == j - 1)
    {
        if (a[i] > a[j])
        {
            *max = a[i];
            *min = a[j];
        }
        else
        {
            *max = a[j];
            *min = a[i];
        }
    }
    else
    {
        int mid = (i + j) / 2;
        int max1, min1;
        minmax(i, mid, max, min);
        minmax(mid + 1, j, &max1, &min1);
        if (max1 > *max)
            *max = max1;
        if (min1 < *min)
            *min = min1;
    }
}

int main()
{
    int i;
    int min = a[0], max = a[0];
    minmax(0, 8, &max, &min);
    printf("Min = %d\nMax = %d", min, max);
}