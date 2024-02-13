#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct articol{
    char *titlu;
    char *text;
} Articol;

void citireFisier(Articol **p, int *nrArticole, FILE *fin)
{
    int textlenght = 0;
    if(fin == NULL)
        printf("Eroare: fisierul nu exista;");
    (*p) = (Articol*) realloc(*p, ((*nrArticole)+1)*sizeof(Articol));
    char line[200];
    fgets(line, 200, fin);
    (*p)[*nrArticole].titlu = malloc(strlen(line));
    strcpy((*p)[*nrArticole].titlu, line);

    fgets(line, 200, fin); // linia 1 care este "\n"

    (*p)[*nrArticole].text = malloc(strlen(line));
    (*p)[*nrArticole].text[0] = '\0'; // asta
    while(fgets(line, 200, fin))
    {
        textlenght += strlen(line);
        (*p)[*nrArticole].text = realloc((*p)[*nrArticole].text, textlenght);
        (*p)[*nrArticole].text[textlenght] = '\0'; // asta
        strcat((*p)[*nrArticole].text, line);
    }

    int i;
    for(i = 0; i < strlen((*p)[*nrArticole].text); i++)
        if((*p)[*nrArticole].text[i] == '\n')
            (*p)[*nrArticole].text[i] = ' '; // aici am modificat

    (*nrArticole) = (*nrArticole) + 1;
}

int compare(const void *A, const void *B)
{
    Articol a = *((Articol*)A);
    Articol b = *((Articol*)B); // aci modificare

    if(!strcmp(a.titlu, b.titlu))
        return strlen(a.text) - strlen(b.text);

    else if(strcmp(a.titlu, b.titlu) < 0) return -1;
        else return 1;
}

void afisare(Articol *a, int nrArticole)
{
    int i;
    for (i = 0; i < nrArticole; i++)
        printf("%s\n%s\n\n\n", a[i].titlu, a[i].text);
}

int main()
{
    FILE *fNasa = fopen("Nasa.txt", "r");
    FILE *fUPB = fopen("UPB.txt", "r");
    FILE *fUB = fopen("UB.txt", "r");
    Articol *articole;
    int nrArticole = 0;

    articole = (Articol*) malloc(sizeof(Articol));
    citireFisier(&articole, &nrArticole, fNasa); 
    citireFisier(&articole, &nrArticole, fUPB); 
    citireFisier(&articole, &nrArticole, fUB); 

    afisare(articole, nrArticole);

    printf("Dupa sortarea lexicografica a articolelor: \n");
    qsort(articole, nrArticole, sizeof(articole[0]), compare);
    afisare(articole, nrArticole);

    return 0;
}