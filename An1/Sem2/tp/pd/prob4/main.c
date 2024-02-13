#include <stdio.h>
#include <stdlib.h>

int pd(int n)
{
    int i;
    int *Nx = (int *)calloc((n + 1), sizeof(int));
    int *Ny = (int *)calloc((n + 1), sizeof(int));
    int *Nz = (int *)calloc((n + 1), sizeof(int));
    Nx[1] = 1;
    Ny[1] = 1;
    Nz[1] = 1;

    for (i = 2; i <= n; i++)
    {
        Nx[i] = Nz[i - 1];
        Ny[i] = Nz[i - 1];
        Nz[i] = Nx[i - 1] + Ny[i - 1];
    }
    int sum = Nx[n] + Ny[n] + Nz[n];
    free(Nx);
    free(Ny);
    free(Nz);

    return sum;
}

int main()
{
    FILE *fin = fopen("date.in", "r");
    FILE *fout = fopen("date.out", "w");
    int n;

    fscanf(fin, "%d", &n);
    fprintf(fout, "%d", pd(n));

    fclose(fin);
    fclose(fout);
    return 0;
}