#include <stdio.h>

typedef struct{
char nume[41];
float debit_cont;
unsigned int codificat;
int stare_indatorare : 1;
} Client;


void citire(int nrClienti, Client client[])
{
    int i,aux;
    for(i = 0; i < nrClienti; i++)
    {
        printf("Nume: "); scanf("%s", &client[i].nume);
        printf("Debit cont: "); scanf("%f", &client[i].debit_cont);
        printf("Stare Indatorare: "); scanf("%d", &aux); client[i].stare_indatorare = aux;
    }
}

void codificat(int nrClienti, Client client[])
{
    int i;
    for(i = 0; i < nrClienti; i++)
    {

    }
}

int main()
{
    printf("%d", sizeof(Client));
}