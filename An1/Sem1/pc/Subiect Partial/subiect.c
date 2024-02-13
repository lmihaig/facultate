#include <stdio.h>

typedef struct
{
    char nume[41];
    float debit_cont;
    int codificat;
    unsigned stare_indatorare : 1;
} Client;  // sizeof(Client) = 56;

typedef union 
{ 
    float debit;
    unsigned char byte[4]; 
}debitCodif;

void citire(int nrClienti, Client client[])
{
    int i, aux;
    for(i = 0; i < nrClienti; i++)
    {
        printf("Nume: "); scanf("%s", &client[i].nume);
        printf("Debit cont: "); scanf("%f", &client[i].debit_cont);
        printf("Stare indatorare (0 || 1): "); scanf("%u", &aux);  // nu putem accesa locatia membrului din camp de biti asa ca citim in aux si atribuim pe baza de caz
        if(aux == 0) client[i].stare_indatorare = 0;
        else client[i].stare_indatorare = 1;
   }
}

void codificare(int nrClienti, Client client[])
{
    int i;
    char bit;
    for(i = 0; i < nrClienti; i++)
    {
        client[i].codificat = 0;

        debitCodif b;
        b.debit = client[i].debit_cont;

        bit = b.byte[0]; // pentru cel mai seminificativ byte
        while(bit)
        {
            if(!(bit & 1))
                client[i].codificat++;
            bit >>= 1;
        }
        
        bit = b.byte[4]; // pentru ultimul byte
        while(bit)
        {
            if(!(bit & 1))
                client[i].codificat++;
            bit >>= 1;
        }
    }
}

void scriereFisier(FILE* fout, int nrClienti, Client client[])
{
    int i;
    for(i = 0; i < nrClienti; i++)
        fprintf(fout, "%s \t %.4f \t %d \n", client[i].nume, client[i].debit_cont, client[i].stare_indatorare); // tiparirea in fisier a campurilor aferente fiecarui client, tipul float cu 4 zecimale
}


int main()
{   
    
    Client client[100], clientAfis;
    int nrClienti, i, aux;
    printf("Numarul de clienti: "); scanf("%d", &nrClienti);
    
    FILE* fout = fopen("date.txt", "w");
    citire(nrClienti, client);
    scriereFisier(fout, nrClienti, client);
    fclose(fout); // inchidem fisierul pt a il redeschide mai tarziu

    codificare(nrClienti, client);

    FILE* fin = fopen("date.txt", "r");
    if(fin == NULL)
    {
        printf("Fisierul este gol \n");
        return 0;
    }

    printf("Numele clientilor neindatorati cu debite peste 200: \n");
    for(i = 0; i < nrClienti; i++)
        {
            fscanf(fin,"%s %f %u", &clientAfis.nume, &clientAfis.debit_cont, &aux);
            clientAfis.stare_indatorare = aux;
            if(!clientAfis.stare_indatorare && clientAfis.debit_cont > 200) 
                printf("%s \n", clientAfis.nume);
        }
    fclose(fin); // inchidem fisierul pt ca am terminat de lucrat cu el

    return 0;
}