#include <stdio.h>
int binary_search(char arr[], int low, int high, char key)
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

int main()
{
    char arr[] = {'B', 'C', 'E', 'I', 'J', 'M', 'O', 'P', 'R', 'W', 'Y'};
    int n = 11;
    char key;
    printf("Enter key: ");
    scanf("%c", &key);
    int a = binary_search(arr, 0, n - 1, key);
    if (a == -1)
    {
        printf("Element not found");
    }
    else
    {
        printf("Element found at %d", a+1);
    }
}