// Nume
// Grupa
// nr subiect
// compilat cu gcc/clang/microsoft visual c++ compiler
// compiler flags: gcc.exe -Wall -g -pedantic -Wextra -Wall -std=c99

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SUMA_MAX 100000

struct client {
    char nume[42];  /* 40 de caractere + '\0', inca unul pt \n daca citim cu fgets */
    /// clientii indatorati au credit, nu debit :/
    float debit_cont;  /* nu double pt ca trebuie dimensiune minima */
    /* valoarea maxima pt debit va fi SUMA_MAX */
    int codificat;
    bool stare_indatorare;  // false: neindatorat
    /// sau unsigned stare_indatorare : 1;
};

union bin_float {
    float f;
    unsigned char bytes[sizeof(float)];  // type punning
};

int nr_biti_zero(char c) {
    int j, nr;
    nr = 0;
    for(j = 0; j < 8; j++) {
        if((c & 1) == 0)  // ultimul bit
            nr++;
        c >>= 1;  // trecem la urmatorul bit
    }
    return nr;
}

void codificare(struct client clienti[], int nr_clienti) {
    int i;
    for(i = 0; i < nr_clienti; i++) {
        clienti[i].codificat = 0;
        union bin_float b;
        b.f = clienti[i].debit_cont;
        clienti[i].codificat += nr_biti_zero(b.bytes[0]);  // primul octet
        clienti[i].codificat += nr_biti_zero(b.bytes[3]);  // ultimul octet
    }
}

void citire(struct client clienti[], int nr_clienti) {
    int i, indatorat;
    for(i = 0; i < nr_clienti; i++) {
        // citire nume fara spatii
        printf("nume (max 40 caractere): ");
        scanf("%40s\n", clienti[i].nume);  // fara & pt ca e vector aka pointer
        // citire nume cu spatii
        //fgets(clienti[i].nume, 41, stdin);
        if(clienti[i].nume[strlen(clienti[i].nume)-1] == '\n')
            clienti[i].nume[strlen(clienti[i].nume)-1] = '\0';
        do {
            printf("debit: ");
            scanf("%f\n", &clienti[i].debit_cont);
        } while(clienti[i].debit_cont > SUMA_MAX);
        printf("stare_indatorare (0 - neindatorat, 1 - indatorat): ");
        scanf("%d\n", &indatorat);
        if(!indatorat)
            clienti[i].stare_indatorare = false;
        else
            clienti[i].stare_indatorare = true;
    }
}

void afisare(struct client clienti[], int nr_clienti, bool afis_codif) {
    int i;
    for(i = 0; i < nr_clienti; i++) {
        printf("nume: %s, debit: %f, indatorat: %s", clienti[i].nume,
               clienti[i].debit_cont,
               clienti[i].stare_indatorare ? "da" : "nu");
        if(afis_codif)  printf(", codificat: %d", clienti[i].codificat);
        puts("");
    }
    puts("------------------------------------");
}

void ordonare(struct client clienti[], int nr_clienti) {
    int i, j;
    for(i = 0; i < nr_clienti - 1; i++)
        for(j = i+1; j < nr_clienti; j++)
            if((clienti[i].debit_cont < 1000 && clienti[j].debit_cont >= 1000 &&
                clienti[i].stare_indatorare && clienti[j].stare_indatorare) ||
               (!clienti[i].stare_indatorare && clienti[j].stare_indatorare)) {

                struct client aux;
                aux = clienti[i];
                clienti[i] = clienti[j];
                clienti[j] = aux;
            }
}

void scrie_client(struct client clienti[], int nr_clienti, const char *nume, const char *nf) {
    int i;
    FILE *f;
    f = fopen(nf, "a");
    for(i = 0; i < nr_clienti; i++)
        if(!strcmp(clienti[i].nume, nume)) {
            // presupunem ca numele sunt unice
            fprintf(f, "%s %.0f %s\n", clienti[i].nume,
                    clienti[i].debit_cont,
                    clienti[i].stare_indatorare ? "da" : "nu");
            fclose(f);
            return;
        }
    fprintf(f, "-\n");
    fclose(f);
}

void extrage(const char *nf) {
    FILE *f = fopen(nf, "r");
    struct client cl;
    char stare[3];
    int nr;
    while((nr = fscanf(f, "%40s %f %s\n", cl.nume, &cl.debit_cont, stare)) > 0) {
        if(nr == 3 && cl.debit_cont >= 200)
            printf("nume: %s, debit: %f, datorii: %s\n", cl.nume, cl.debit_cont, stare);
    }
    fclose(f);
}

int main()
{
    //struct client c1;
    //c1.stare_indatorare = false;
    //c1.stare_indatorare = true;
    //printf("sizeof(true): %zu, sizeof(bool): %zu",
    //       sizeof(true), sizeof(bool));

    // 1. citire
    int nr_clienti;
    //FILE *fin;
    //fin = fopen("date.in", "r");
    //fclose(fin);
    printf("nr clienti: ");
    scanf("%d", &nr_clienti);  // am luat si \n ca sa nu il ia fgets
    struct client clienti[nr_clienti];  // valabil doar din C99
    // chestia de mai sus se numeste VLA (variable length array)
    // pt C90: struct client clienti[1000]; // sau cu alocare dinamica
    citire(clienti, nr_clienti);
    afisare(clienti, nr_clienti, false);
    codificare(clienti, nr_clienti);
    afisare(clienti, nr_clienti, true);
    ordonare(clienti, nr_clienti);
    afisare(clienti, nr_clienti, true);
    const char nf[] = "date.txt";
    //scrie_client(clienti, nr_clienti, "asdef2", nf);
    //scrie_client(clienti, nr_clienti, "asde2", nf);
    extrage(nf);
    getchar();
    return 0;
}
