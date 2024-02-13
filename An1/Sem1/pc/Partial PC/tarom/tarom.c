#include <stdio.h>
#include <stdlib.h>

typedef struct{
char nume[31];
enum clasa{A, B} clasaZbor;
float greutateBagaj;
unsigned short int cod;
}Pasager;

void citire(FILE* fin, int nrIntrari, Pasager pas[])
{
    for(int i = 0; i < nrIntrari; i++)
        fscanf(fin, "%s %c %f", &pas[i].nume, &pas[i].clasaZbor, &pas[i].greutateBagaj);

}

void print(FILE* fout, int nrIntrari, Pasager pas[])
{
    for(int i = 0; i < nrIntrari; i++)
       fprintf(fout,"%s %c %.2f %hu \n", pas[i].nume, pas[i].clasaZbor, pas[i].greutateBagaj, pas[i].cod);

}


void completareCod(int nrIntrari, Pasager pas[])
{
    for(int i = 0; i < nrIntrari; i++)
    {
        pas[i].cod = __builtin_popcount(~pas[i].nume[0]);
    }
}

int comparatie(const void *pa, const void *pb)
{
    const int *p1 = pa;
    const int *p2 = pb;
    return *p1 - *p2;
}

int main()
{

    int nrPas = nrPas;

    FILE* fin = fopen("date.in", "r");
    FILE* fout = fopen("date.out", "w");
    Pasager pas[100];
    citire(fin, nrPas, pas);
    completareCod(nrPas, pas);
    qsort(pas, nrPas, sizeof(Pasager), comparatie);
    print(fout, nrPas, pas);
}