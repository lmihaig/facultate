#include <stdio.h>
#include <stdlib.h>

void afisare(FILE *fout, int **arr, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            fprintf(fout, "%d ", arr[i][j]);
        fputs("\n", fout);
    }
}

int valid(int **arr, int n, int sum, int i, int j, int y)
{
    int aux, colSum = y, rowSum = y;
    for (aux = 0; aux < n; aux++)
    {
        if (arr[i][aux] == y || arr[aux][j] == y)
            return 0;
        rowSum += arr[i][aux];
        colSum += arr[aux][j];
    }

    if (colSum > sum || rowSum > sum)
        return 0;

    if ((i == n - 1) && (colSum != sum))
    {
        return 0;
    }

    if ((j == n - 1) && (rowSum != sum))
    {
        return 0;
    }

    return 1;
}

int bkt(FILE *fout, int **arr, int n, int sum)
{
    {
        int i, j, y;
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (arr[i][j] == 0)
                {
                    for (y = 1; y <= sum; y++)
                        if (valid(arr, n, sum, i, j, y))
                        {
                            arr[i][j] = y;
                            if (bkt(fout, arr, n, sum))
                                return 1;
                            arr[i][j] = 0;
                        }
                    return 0;
                }

        afisare(fout, arr, n);
        return 1;
    }
}

int main()
{
    int n, sum, i;
    FILE *fin = fopen("date.in", "r");
    FILE *fout = fopen("date.out", "w");

    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &sum);

    int **array = (int **)calloc(n, sizeof(int *));
    for (i = 0; i < n; i++)
        array[i] = (int *)calloc(n, sizeof(int));

    if (!bkt(fout, array, n, sum))
        fprintf(fout, "Nu s-a gasit o solutie.");

    fclose(fin);
    fclose(fout);
    for (i = 0; i < n; i++)
        free(array[i]);
    free(array);
}