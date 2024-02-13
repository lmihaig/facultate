#include <stdio.h>
#include <stdlib.h>
/// Precizare: ultimul subpunct este luat de la modelul 3, daca e cineva interesat de cum s-ar face cel de la modelul 4 va rog sa imi spuneti si o sa modific subpunctul d
/// Acesta este modelul 4 cu precizarea ca ultimul subpunct este luat din modelul 3. Modelul acesta a fost rezolvat la tutoriat deci puteti vedea inregistrarea
/// Daca nu intelegeti ceva la aceasta sursa sau oricare alta astept orice fel de intrebari.
struct tarom
{
    char nume[31];
    char clasa_zbor;
    float greutate_bagaj;
    int cod;
};

void citire(struct tarom v[100], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("nume: ");
        scanf("%s", v[i].nume);
        printf("clasa zbor: ");
        getchar();
        scanf("%c", &v[i].clasa_zbor);
        printf("greutate bagaj: ");
        scanf("%f", &v[i].greutate_bagaj);
    }
}

void afisare_fara_cod(struct tarom v[101], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("nume %s, clasa zbor %c, greutate bagaj %f \n",v[i].nume, v[i].clasa_zbor, v[i].greutate_bagaj);
    }
}

void afisare_cu_cod(struct tarom v[101], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("nume %s, clasa zbor %c, greutate bagaj %f, cod %d \n",v[i].nume, v[i].clasa_zbor, v[i].greutate_bagaj, v[i].cod);
    }
}

void codificare(struct tarom v[100], int n)
{
    int i, count, aux;
    for(i = 0; i < n; i++)
    {
        count = 0;
        aux = v[i].nume[0];
        while(aux > 0)
        {
            if(aux % 2 == 0)
                count ++;
            aux = aux /2;
        }
        v[i].cod = count;
    }
}

void citire_fisier()
{
    int i;
    char nume[31];
    char clasa;
    float greutate;
    FILE *f = fopen("fisier.txt", "r");
    if(f == NULL)
        printf("fisierul nu exista \n");
    else
    {
        while(fscanf(f,"%s",nume) != EOF)
        {
            fscanf(f," %c", &clasa);
            fscanf(f,"%f", &greutate);
            if(greutate > 30.0 && clasa == 'B')
                printf("nume %s, clasa zbor %c, greutate bagaj %f \n",nume, clasa, greutate);
        }
    }
}

int main()
{
    int n, i, j;
    struct tarom v[100], aux;
    printf("Dati numarul de calatori: ");
    scanf("%d", &n);
    citire(v,n);
    afisare_fara_cod(v,n);
    printf("\n");
    codificare(v,n);
    afisare_cu_cod(v,n);
    printf("\n");
    for(i = 0; i < n-1; i++)
        for(j = i+1; j < n; j++)
            if(v[i].greutate_bagaj < v[j].greutate_bagaj)
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
    afisare_fara_cod(v,n);
    citire_fisier();
    return 0;
}
