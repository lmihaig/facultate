#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int a, b;
} interval;

int cmp(const void *x, const void *y)
{
    interval *intervalX = (interval *)x;
    interval *intervalY = (interval *)y;

    return (intervalX->a - intervalY->a);
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void greedy(FILE *fout, interval *inter, int n)
{
    interval aux;
    int i;
    aux.a = inter[0].a;
    aux.b = inter[0].b;

    for (i = 1; i < n; i++)
    {
        if (aux.b >= inter[i].a)
            aux.b = max(aux.b, inter[i].b);
        else
        {
            fprintf(fout, "%d %d\n", aux.a, aux.b);
            aux.a = inter[i].a;
            aux.b = inter[i].b;
        }
    }
    fprintf(fout, "%d %d", aux.a, aux.b);
}

int main()
{
    FILE *fin = fopen("date.in", "r");
    FILE *fout = fopen("date.out", "w");
    int n, i;

    fscanf(fin, "%d", &n);
    interval *inter = (interval *)malloc(n * sizeof(interval));
    for (i = 0; i < n; i++)
        fscanf(fin, "%d%d", &inter[i].a, &inter[i].b);

    qsort(inter, n, sizeof(interval), cmp);
    greedy(fout, inter, n);
    fclose(fin);
    fclose(fout);
    free(inter);

    return 0;
}