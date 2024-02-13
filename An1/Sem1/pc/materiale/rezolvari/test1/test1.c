#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct produs{
    char nume[30];
    float pret, distanta;
    struct locatie *L;
} Produs;

typedef struct locatie{
    char *nume_sector;
    int gps_x, gps_y;
} Locatie;

void citire(Produs **p, int *nrProduse, FILE* fin)
{
    *nrProduse = 0;
    *p = (Produs*) malloc(sizeof(Produs));
    char line[200];
    while(fgets(line, 200, fin))
    {   
        *p = (Produs*) realloc(*p, ((*nrProduse) + 1)*sizeof(Produs));
        char *fields = strtok(line, ", ");
        strcpy((*p)[*nrProduse].nume, fields); 
        fields = strtok(NULL,", "); 
        (*p)[*nrProduse].pret = atof(fields); 
        fields = strtok(NULL,", "); 
        (*p)[*nrProduse].L = (Locatie*) malloc(2*sizeof(Locatie));
        (*p)[*nrProduse].L[1].nume_sector = NULL;
        int indexLocatie = 0; 

        while (fields)
        {
            (*p)[*nrProduse].L = realloc((*p)[*nrProduse].L, (indexLocatie + 2)*sizeof(Locatie));
            (*p)[*nrProduse].L[indexLocatie + 1].nume_sector = NULL;
            (*p)[*nrProduse].L[indexLocatie].nume_sector = malloc(strlen(fields));
            strcpy((*p)[*nrProduse].L[indexLocatie].nume_sector, fields); 
            fields = strtok(NULL,", ");
            (*p)[*nrProduse].L[indexLocatie].gps_x = atoi(fields); 
            fields = strtok(NULL,", ");
            (*p)[*nrProduse].L[indexLocatie].gps_y = atoi(fields);
            fields = strtok(NULL,", ");
            indexLocatie++;
        }
        (*nrProduse) = (*nrProduse) + 1;
    }
}

void distanta(Produs **p, int n)
{
    int i,j,k;
    for(i = 0; i < n; i++)
    {
        float maxim = 0;
        for(j = 0 ; (*p)[i].L[j].nume_sector != NULL; j++)
            for(k = j + 1 ; (*p)[i].L[k].nume_sector != NULL; k++)
                {
                    int x = (*p)[i].L[k].gps_x - (*p)[i].L[j].gps_x;
                    int y = (*p)[i].L[k].gps_y - (*p)[i].L[j].gps_y;

                    float dist = sqrt(x*x + y*y);
                    if(dist > maxim)
                        maxim = dist;
                }
    (*p)[i].distanta = maxim;
    }
}

void afisare(Produs *p, int n)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        printf("%s ", p[i].nume);
        printf("%.2f ", p[i].pret);
        printf("%.2f ", p[i].distanta);
        for(j = 0 ; p[i].L[j].nume_sector != NULL; j++)
        {
            //printf("%p \n", p[i].L[j].nume_sector);
            printf("%s %d %d ", p[i].L[j].nume_sector, p[i].L[j].gps_x, p[i].L[j].gps_y);
        }
        printf("\n");
    }
    
}

int dupe(Produs p)
{
    int i,j, aparitie, dupeCount = 0;
    for(i = 0; p.L[i].nume_sector != NULL ; i++)
        {
            for(j = i + 1; p.L[j].nume_sector != NULL ; j++)
                if(!strcmp(p.L[i].nume_sector, p.L[j].nume_sector))
                    {
                        dupeCount++;
                        break;
                    }
        }
    return dupeCount;
}

int compare(Produs a, Produs b)
{
    return dupe(a) - dupe(b);
}

int main()
{

    Produs *p;
    int nrProd;
    FILE *fin = fopen("fisier.txt", "r");

    if(fin == NULL)
        printf("Eroare: fisierul nu exista;");

    citire(&p, &nrProd, fin);
    distanta(&p, nrProd);
    printf("Inainte de sortare: \n");
    afisare(p, nrProd);
    printf("\n");

    qsort(p, nrProd, sizeof(p[0]), compare);
    printf("Dupa sortare: \n");
    afisare(p, nrProd);
    
    return 0;
}