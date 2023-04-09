#include <stdio.h>
#include <stdlib.h>
#define max 100
void merge_sort(char arr[], int low, int high);
void merge(char arr[], int low, int mid, int high);
int binary_search(char arr[], int low, int high, int key);
int b[100];
int main()
{
    char arr[max];
    int n = 11, i;
    printf("Enter the size: ");
    scanf("%d", &n);
    printf("Enter the characters:\n");
    for (i = 0; i < n; i++)
    {
        getchar();
        scanf("%c", &arr[i]);
    }
    merge_sort(arr, 0, n - 1);
    printf("Sorted list:\n");
    for (i = 0; i < n; i++)
    {
        printf("%c ", arr[i]);
    }
    char key;
    printf("\nEnter key: ");
    getchar();
    scanf("%c", &key);
    int a = binary_search(arr, 0, n - 1, key);
    if (a == -1)
    {
        printf("Element not found");
    }
    else
    {
        printf("%c found at %d", key, a + 1);
    }
}
void merge_sort(char arr[], int low, int high)
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

void merge(char arr[], int low, int mid, int high)
{
    int i, j, k;
    i = low;
    j = mid + 1;
    k = low;
    while ((i <= mid) && (j <= high))
    {
        if (arr[i] <= arr[j])
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

int binary_search(char arr[], int low, int high, int key)
{
    int mid;
    if (low == high)
    {
        if (arr[low] == key)
            return low;
        else
            return -1;
    }
    else
    {
        mid = (low + high) / 2;
        if (arr[mid] == key)
            return mid;
        else if (arr[mid] > key)
            return binary_search(arr, low, mid - 1, key);
        else
            return binary_search(arr, mid + 1, high, key);
    }
}