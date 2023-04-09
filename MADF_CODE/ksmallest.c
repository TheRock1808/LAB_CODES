#include <stdio.h>
#define max 20
int arr[max];
void swap(int *a, int *b);
int quickSort(int a[], int low, int high, int k);
int partition(int a[], int low, int high);
int quickSort(int a[], int low, int high, int k)
{
    if (low == high)
        return a[low];
    int pivot = partition(a, low, high);
    int count = pivot - low + 1;
    if (count == k)
        return a[pivot];
    else if (count > k)
        return quickSort(a, low, pivot - 1, k);
    else
        return quickSort(a, pivot + 1, high, k - count);
}
int partition(int a[], int low, int high)
{
    int loc, i, j;
    loc = a[low];
    i = low;
    j = high + 1;
    while (i < j)
    {
        do
            i++;
        while (a[i] <= loc && i <= high);
        do
            j--;
        while (loc <= a[j] && j >= low);
        if (i < j)
        {
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[j], &a[low]);
    return (j);
}
int main()
{
    int n, m;
    printf(" Enter kth element: ");
    scanf("%d", &n);
    printf("enter the no of elements: ");
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf(" \nBefore sorting: ");
    for (int i = 0; i < m; i++)
        printf("%d ", arr[i]);
    int k = quickSort(arr, 0, m - 1, n);
    printf(" After quicksort: ");
    for (int i = 0; i < m; i++)
        printf("%d ", arr[i]);
    printf(" kth smallest is %d", k);
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
