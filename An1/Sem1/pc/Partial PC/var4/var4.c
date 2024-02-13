#include <stdio.h>

typedef struct{
    float greutate_bagaj;
    int cod;
    char nume[31];
    char clasa_zbor : 1;
} Tarom;

void citire(int nrPasageri, Tarom pas[])
{
    int aux, i;
    for(i = 0; i < nrPasageri; i++)
    {
        printf("Nume: "); scanf("%s", &pas[i].nume);
        printf("Clasa zbor: ");  scanf("%c", &aux); pas[i].clasa_zbor=aux;
        printf("Greutate bagaj: "); scanf("%f", &pas[i].greutate_bagaj);
    }
}

void codificare(int nrPasageri, Tarom pas[])
{
    for(int i = 0; i < nrPasageri; i++)
        pas[i].cod = __builtin_popcount(~pas[i].nume[0]);
}

int main()
{
    FILE* fin = fopen("var4.in", "r");
    FILE* fout = fopen("var4.out", "w");
    Tarom pas[100];
    unsigned int nrPasageri = 3;
    //citire(nrPasageri, pas);
    //printf("%d", sizeof(Tarom));
}