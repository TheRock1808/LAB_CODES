#include <stdio.h>
#include <stdlib.h>
#define max 100
void merge_sort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int high);
int b[100];
int main()
{
    int n = 11, i;
    int arr[max];
    printf("Enter the size: ");
    scanf("%d", &n);
    printf("Enter the characters:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    merge_sort(arr, 0, n - 1);
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}
void merge_sort(int arr[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
        int i;
        for (i = low; i <= high; i++)
            arr[i] = b[i];
    }
}

void merge(int arr[], int low, int mid, int high)
{
    int i, j, k;
    i = low;
    j = mid + 1;
    k = low;
    while ((i <= mid) && (j <= high))
    {
        if (arr[i] >= arr[j])
        {
            b[k] = arr[i];
            i++;
        }
        else
        {
            b[k] = arr[j];
            j++;
        }
        k++;
    }
    if (i <= mid)
        while (i <= mid)
            b[k++] = arr[i++];
    else
        while (j <= high)
            b[k++] = arr[j++];
}