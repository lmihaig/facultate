#include <stdio.h>
#include <stdlib.h>

void fill(int **arr, int x, int y, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            arr[x + i][y + j] = 1;
}

void topright(int **arr, int x, int y, int rows, int cols)
{
    int i, j;
    rows /= 2;
    cols /= 2;
    if (rows == 0 || cols == 0)
        return;
    else
    {
        topright(arr, x, y, rows, cols);
        fill(arr, x, y + cols, rows, cols);
        topright(arr, x + rows, y, rows, cols);
        topright(arr, x + rows, y + cols, rows, cols);
    }
}

void write_array(FILE *file, int n, int m, int **array)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            fprintf(file, "%d ", array[i][j]);
        fputs("\n", file);
    }
}

int main()
{
    int n, i, j;
    FILE *fin = fopen("date.in", "r");
    FILE *fout = fopen("date.out", "w");
    fscanf(fin, "%d", &n);
    unsigned int rows = 1 << n;
    int **array = (int **)malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++)
        array[i] = (int *)malloc(rows * sizeof(int));
    for (i = 0; i < rows; i++)
        for (j = 0; j < rows; j++)
            array[i][j] = 0;
    topright(array, 0, 0, rows, rows);
    write_array(fout, rows, rows, array);
}