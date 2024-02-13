#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct magazin {
    char nume[30];
    int gps_x, gps_y;
} Magazin;

typedef struct produs {
    char nume[30];
    float pret;
    struct magazin *m;
} Produs;

typedef struct nod {
    Produs prod;
    struct nod *urm;
} Nod;

void citire(Produs **p, int *nrProduse)
{
    *nrProduse = 0;
    *p = (Produs*) malloc(sizeof(Produs));
    char data[100];
    while(fgets(data, 100, stdin))
    {
        *p = realloc(*p,((*nrProduse)+1)*sizeof(Produs)); // produs nou
        char *fields = strtok(data," "); // fields retine numele
        strcpy((*p)[*nrProduse].nume, fields); // alocam numele
        fields = strtok(NULL," "); // fields retine pretul (ca *char)
        (*p)[*nrProduse].pret = atof(fields); // alocam pretul
        fields = strtok(NULL," "); // fields aici retine magazinul
        
        (*p)[*nrProduse].m = (Magazin*) malloc(sizeof(Magazin));
        int indexMagazine = 0;

        while(fields)
        {
            (*p)[*nrProduse].m = realloc((*p)[*nrProduse].m, (indexMagazine + 1)*sizeof(Magazin));
            strcpy((*p)[*nrProduse].m[indexMagazine].nume, fields);
            fields = strtok(NULL," "); // fields aici retine coordx
            (*p)[*nrProduse].m[indexMagazine].gps_x = atoi(fields);
            fields = strtok(NULL," "); // fields aici retine coordy
            (*p)[*nrProduse].m[indexMagazine].gps_y = atoi(fields);
            fields = strtok(NULL," "); // aici retine urmatorul magazin sau NULL
            indexMagazine++;
        }
    }
}

void findMagazin()
{

}

int compare()
{

}

void eliminare(struct nod **L, char *nume)
{

}

int main()
{

Produs *produse;
int nrProd;

citire(&produse, &nrProd);
printf(produse[0].m[0].nume);

}