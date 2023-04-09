#include <stdio.h>
#include<stdlib.h>
#define max 100
void bubble_sort(int a[], int n)
{
    int i, j, tmp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void insertion_sort(int arr[], int n)
{
    int i, j, k;
    for (i = 0; i < n - 1; i++)
    {
        k = arr[i];
        for (j = i - 1; j >= 0 && k < arr[j]; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = k;
    }
}

void selection_sort(int arr[], int n)
{
    int i, j, min, tmp;
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[min] > arr[j])
                min = j;
        }
        if (i != min)
        {
            tmp = arr[i];
            arr[i] = arr[min];
            arr[min] = tmp;
        }
    }
}

void shell_sort(int arr[], int n)
{
    int i, j, incr, k;
    printf("Enter the maximum increment (odd value): ");
    scanf("%d", &incr);
    while (incr >= 1)
    {
        for (i = incr; i < n; i++)
        {
            k = arr[i];
            for (j = i - incr; j >= 0 && k < arr[j]; j = j - incr)
                arr[j + incr] = arr[j];
            arr[j + incr] = k;
        }
        incr = incr - 2;
    }
}

void display(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int a[], int tmp[], int l, int mid, int up)
{
    int i = l, t;
    int j = mid + 1;
    int k = l;
    while ((i <= mid) && (j <= up))
    {
        if (a[i] < a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    while (i <= mid)
        tmp[k++] = a[i++];

    while (j <= up)
        tmp[k++] = a[j++];

    for (t = l; t <= up; t++)
        a[t] = tmp[t];
}

void merge_sort(int arr[], int low, int up)
{
    int mid, tmp[max];
    if (low < up)
    {
        mid = (low + up) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, up);
        merge(arr, tmp, low, mid, up);
    }
}

void linear_search(int arr[], int n, int key)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (key == arr[i])
        {
            printf("%d found at location %d\n", key, i + 1);
            return;
        }
    }
    printf("%d does not present", key);
}

void binary_search(int arr[], int n, int key)
{
    int mid, low, high;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (key > arr[mid])
            low = mid + 1;
        else if (key < arr[mid])
            high = mid - 1;
        else
        {
            printf("%d found at location %d\n", key, mid + 1);
            return;
        }
    }
    printf("%d does not present", key);
}

int main()
{
    //86 45 41 71 31 40 90 95 16 21

    int a[max], n, ch, i, j, item;
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    printf("Enter the elements in the array:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    while (1)
    {
        printf("1: Bubble sort\n2: Selection sort\n3: Insertion sort\n4: Shell sort\n5: Merge sort\n6: Linear Search\n7: Binary Search\n8: Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            bubble_sort(a, n);
            display(a, n);
            break;
        case 2:
            selection_sort(a, n);
            display(a, n);
            break;
        case 3:
            insertion_sort(a, n);
            display(a, n);
            break;
        case 4:
            shell_sort(a, n);
            display(a, n);
            break;
        case 5:
            merge_sort(a, 0, n - 1);
            display(a, n);
            break;
        case 6:
            printf("Enter the item to searched: ");
            scanf("%d", &item);
            linear_search(a, n, item);
            break;
        case 7:
            printf("Enter the item to searched: ");
            scanf("%d", &item);
            binary_search(a, n, item);
            break;
        case 8:
            exit(1);
            break;
        default:
            printf("Wrong Input\n");
            break;
        }
    }
}