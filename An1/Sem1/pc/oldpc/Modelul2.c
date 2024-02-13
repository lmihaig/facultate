/// NICOI ALEXANDRU - CALCULATOARE SI TEHNOLOGIA INFORMATIEI - GRUPA 253
/// TUTORIAT PROGRAMAREA CALCULATOARELOR 2020-2021, SERIA 16
/// REZOLVARE TEST LABORATOR 1 2019 , NR. 2

#include <stdio.h>
#include <stdlib.h>

typedef union { /// folosim aceeasi zona de memorie pt numarul in virgula mobila, dar si pt char byte
                /// deoarece un char are 1 byte, si putem accesa f ez cu vector de bytes cei 4 bytes ai lui float debit
                /// so yeah, cand facem &, se face byte-ul in binary si putem indeplini cerinta
                /// virgula mobila ~ ceva gen binary64, dar fara sa ne ducem cu mantisa pana la 64 cu 0
    float debit;
    unsigned char byte[4]; /// byte[4] -> accesam cei 4 byte ai debitului (manevra eficienta si singura de folos
                           ///                                                              pentru union)
}typedebit;

struct client
{
    char nume[40];
    typedebit debit_cont;
    unsigned int codificat;
    unsigned int stare_indatorare : 1;
};

/// 1
void citire(struct client v[101], int n)
{
    for(int i = 0 ; i < n ; i++)
    {
        printf("Numele clientului %d : ",i);
        scanf("%s",v[i].nume);
        printf("Debit cont clientul %d : ",i);
        scanf("%f",&v[i].debit_cont.debit);
        int x;
        printf("Stare indatorare clientul %d (1 - indatorat , 0 - neindatorat) : ",i);
        scanf("%d",&x);
        if(x == 1)
            v[i].stare_indatorare = 1;
        else v[i].stare_indatorare = 0;}
}

/// 2
void codif(struct client v[101], int n) {
    for(int i = 0 ; i < n ; i++) {
        v[i].codificat = 0;
        unsigned char bit = v[i].debit_cont.byte[0];
        while(bit)
        {
            if((bit & 1) == 0)
                v[i].codificat++;
            bit = bit >> 1;
        }
        bit = v[i].debit_cont.byte[3];
        while(bit) {
            if((bit & 1) == 0)
                v[i].codificat++;
            bit = bit >> 1;
        }
    }

}

/// 3
int cmp(struct client a, struct client b)
{
    if(a.stare_indatorare == 1 && b.stare_indatorare == 0)
        return -1;
    else if(a.stare_indatorare == 0 && b.stare_indatorare == 0)
        return 0;
    else if(a.stare_indatorare == 0 && b.stare_indatorare == 1)
        return 1;
    else if(a.stare_indatorare == 1 && b.stare_indatorare == 1)
    {
        if(a.debit_cont.debit > 1000 && b.debit_cont.debit <= 1000)
            return -1;
        else if(a.debit_cont.debit <= 1000 && b.debit_cont.debit > 1000)
            return 1;
        else return 0; /// inseamna ca ori sunt ambele > 1000 , ori <= 1000
    }
}

void sortare(struct client v[101], int n)
{

    qsort(v,n,sizeof(struct client),cmp);
}

/// 4
/// scriere fisier
void scrierefisier(struct client a)
{
    FILE *f = fopen("fisier.cti","w");
    if(f == NULL)
    {
        printf("\nFisierul nu exista.\n");
        return;
    }
    if(a.nume[0] == NULL)
        fprintf(f,"%c ",'-');
    else fprintf(f,"%s ",a.nume);
    if(a.debit_cont.debit > 100000 || a.debit_cont.debit < 0)
        fprintf(f, "%c ",'-');
    else fprintf(f,"%d ",(int)a.debit_cont.debit);
    if(a.stare_indatorare != 0 && a.stare_indatorare != 1)
        fprintf(f, "%c\n",'-');
    else fprintf(f,"%u",a.stare_indatorare);
    fclose(f);
}

void citirefisier()
{
    char nume[40];
    char debit[6]; /// < 100000 , vom citi ca string pt ca putem avea '-' :(
    char stare_indatorare;
    FILE *f = fopen("fisier.cti","r");
    while(!feof(f))
    {
        int OK = 1;
        fscanf(f,"%s %s %c", nume, debit, &stare_indatorare);
        if(nume[0] == '-')
        {
            printf("Nume invalid!\n");
            OK = 0;
        }
        else if(debit[0] == '-')
        {
            printf("Debit invalid!\n");
            OK = 0;
        }
        else if(stare_indatorare == '-')
        {
            printf("Stare indatorare invalida!\n");
            OK = 0;
        }
        /// se poate folosi si instructiunea "continue" in loc sa ne folosim de OK, gen la fiecare if
        /// punand "continue", va da skip la celelalte verificari pt ca-s inutile
        if(OK == 1)
        {
            if(stare_indatorare == '0') {
                int debitnr = atoi(debit);
                if (debitnr > 200)
                    printf("%s\n", nume);
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    struct client v[101];
    /// 1
    citire(v,n);
    /// 2
    codif(v,n);
    /// 3
    sortare(v,n);
    /// 4
    scrierefisier(v[0]);
    citirefisier();
    return 0;
}