#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produs{
    char nume[16];
    float pret;
    char **cod;
} Produs;


void citire(Produs **p, int *n)
{
    int i;
    *n = 0;
    *p = (Produs*) malloc(sizeof(Produs));
    char line[21];
    while(fgets(line, 21, stdin))
    {
        if(!strcmp(line,"\n"))
            break;
        *p = (Produs*) realloc(*p, ((*n)+1)*sizeof(Produs));
        char *informatii  = strtok(line, " ");
        strcpy((*p)[(*n)].nume, informatii);
        informatii = strtok(NULL, " ");
        (*p)[(*n)].pret = atof(informatii);
        (*p)[(*n)].cod = (char**) malloc(4*sizeof(char*));
        for(i = 0; i < 4; i++)
            (*p)[(*n)].cod[i]=(char*) malloc(4*sizeof(char));
        (*n) = (*n) + 1;
    }

}

void matriceCod(Produs **p, int n)
{

}

void afisare(Produs *p , int n)
{
    int i, j, k;
    for(i = 0; i < n; i++)
        {
            printf("Nume: %s \n Pret: %.2f \n", p[i].nume, p[i].pret);
            for(j = 0; j < 4; j++)
                for(k = 0; k < 4 ; k++)
                    printf("%c", p[i].cod[j][k]);
                printf("\n");
        }
}

int main()
{
    Produs *p;
    int nrProd;
    
    citire(&p, &nrProd);
    matriceCod(&p, nrProd);
    afisare(p, nrProd);
}