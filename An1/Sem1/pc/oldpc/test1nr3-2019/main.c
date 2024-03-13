#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100

typedef struct
{
    char nume[51];
    float greutate_bagaj;
    unsigned cod : 3;  // se poate si cu 3, dar trebuie sa fim atenti
    unsigned clasa : 2;// 00: 0, 01: 1, 10: 2, 11: 3
    //char clasa : 2;  // 00: 0, 01: 1, 10: -0, 11: -1

    // explicatii pt cod
    // 0...127 -> 2^7 - 1
    // acesti 7 biti pot fi toti 0 sau toti 1
    // asta inseamna ca avem de la 0000000 la 1111111
    // adica nr de biti de zero va fi
    // intre 0 si 7, deci avem nevoie de 2^3
    // totusi, putem observa ca 0 nu va fi niciodata
    // pt ca 0 este caracterul nul (\0), deci sunt
    // suficienti 2^3 - 1 biti

    /*
    0000001
    1000000
    0001000
    0100000
    */
    // campurile trebuie ordonate (des)crescator
    // dupa sizeof
} pasager;

void citeste(pasager pasageri[], int *nr_pasageri)
{
    int i;
    char cat;

    printf("nr pasageri: ");
    fscanf(stdin, "%d", nr_pasageri); // fara & ca e deja pointer
    for(i = 0; i < *nr_pasageri; i++)
    {
        printf("nume: ");
        fscanf(stdin, "%50s", // %c %f",
               pasageri[i].nume);//, &cat,
        //&pasageri[i].greutate_bagaj);
        do
        {
            printf("cat: ");
            scanf("%c", &cat);
        }
        while(cat < 'A' || cat > 'D');
        do
        {
            printf("greutate bagaj: ");
            scanf("%f", &pasageri[i].greutate_bagaj);
        }
        while(pasageri[i].greutate_bagaj > 100
                || pasageri[i].greutate_bagaj < 0);
        pasageri[i].clasa = cat - 'A';
        pasageri[i].cod = 0;
    }
}

void afiseaza(pasager pasageri[], int nr_pasageri)
{
    int i;
    puts("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    for(i = 0; i < nr_pasageri; i++)
        printf("nume: %s, clasa: %c, bagaj: %f, cod: %u\n",
               pasageri[i].nume, pasageri[i].clasa + 'A',
               pasageri[i].greutate_bagaj,
               pasageri[i].cod);
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~");
}

int nr_biti_zero(char c)
{
    int i, nr = 0;
    // 8 pt ca char are (in 99% din cazuri) 8 biti
    for(i = 0; i < 8; i++)
        if((c & (1 << i)) == 0)
            nr++;
    return nr;
}

void codifica(pasager pasageri[], int nr_pasageri)
{
    int i;
    for(i = 0; i < nr_pasageri; i++)
    {
        pasageri[i].cod = nr_biti_zero(pasageri[i].nume[0]);
    }
}

void ordoneaza(pasager pasageri[], int nr_pasageri)
{
    int i, j;
    pasager aux;
    for(i = 0; i < nr_pasageri - 1; i++)
        for(j = i + 1; j < nr_pasageri; j++)
            if(pasageri[i].clasa > pasageri[j].clasa)
            {
                aux = pasageri[i];
                pasageri[i] = pasageri[j];
                pasageri[j] = aux;
            }
}

void selectie(const char *nf)
{
    FILE *fin;
    fin = fopen(nf, "r");
    if(fin == NULL)
    {
        printf("Eroare la deschiderea fisierului %s\n", nf);
        return;
    }
    pasager p;
    char clasa;
    while((fscanf(fin, "%50s %c %f", p.nume, &clasa, &p.greutate_bagaj)) == 3)
    {
        if(p.greutate_bagaj > 30)
            printf("%s\n", p.nume);
    }
    fclose(fin);
}

int main()
{
    //pasager p;
    //p.clasa = 3;
    //printf("%zu", sizeof(pasager));
    pasager pasageri[MAX_N];
    int nr_pasageri;
    citeste(pasageri, &nr_pasageri);
    afiseaza(pasageri, nr_pasageri);
    codifica(pasageri, nr_pasageri);
    afiseaza(pasageri, nr_pasageri);
    ordoneaza(pasageri, nr_pasageri);
    afiseaza(pasageri, nr_pasageri);
    selectie("date.txt");
    return 0;
}
