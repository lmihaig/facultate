#include <stdio.h>
#include <stdlib.h>

int partition(int *arr, int left, int right)
{
    int x = arr[right], i = left, j, temp;
    for (j = left; j < right; j++)
        if (arr[j] <= x)
        {
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return i;
}

int quickselect(int n, int *arr, int k)
{
    int left = 0;
    int right = n - 1;
    int index;
    while (left <= right)
    {
        index = partition(arr, left, right);
        if (index == n - k)
            return arr[index];
        else if (index > n - k)
            right = index - 1;
        else
            left = index + 1;
    }
    return 0;
}

int main()
{
    int n, k, i;

    FILE *fin = fopen("date.in", "r");
    FILE *fout = fopen("date.out", "w");
    fscanf(fin, "%d %d", &n, &k);

    int *arr = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        fscanf(fin, "%d", &arr[i]);
    fprintf(fout, "%d", quickselect(n, arr, n - k + 1));
}