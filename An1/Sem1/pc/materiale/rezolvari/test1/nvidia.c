#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct locatie
{
    char* nume_sector;
    int gps_x;
    int gps_y;
};

struct produs
{
    char nume[30];
    float pret;
    int nr_loc; /// numar de locatii (setat de noi)
    float distanta_maxima; /// distanta maxima calculata la cerinta 2
    struct locatie *L;
};

struct nod
{
    struct produs info; /// vezi cerinta 4
    struct nod* urm;
};
///1
void citire(struct produs **v, int *m) /// m - nr de elemente, asa l am denumit ca parametru aici
{
    FILE *f = fopen("fisier.txt","r"); /// deschidem fisierul "fisier.txt" pe read
    int n = 0; /// initializam nr de produse cu 0
    (*v) = (struct produs*)malloc(1*sizeof(struct produs)); /// alocam dinamic vectorul de produse cu 1 element (vezi 1*sizeof...)
    if(f == NULL)
        printf("eroare"); /// verificam daca exista fisierul
    char s[255]; /// stringul in care citim linia din fisier
    while(fgets(s,255,f)!= 0) /// chestia asta citeste toata linia, nu stiu cum dar da
    {
        n++; /// crestem numarul de produse
        char *p = strtok(s,", "); /// in p avem primul sir pana in `,` din fisier
        int cnt = 1; /// numaram subsirurile ca sa stim cand ajugen la locatii
        while(p) /// cat timp exista subsirurile din sir
        {

            (*v) = (struct produs*)realloc((*v),n*sizeof(struct produs)); /// pt ca adaugam un produs, realocam vectorul cu inca o unitate
                                                                            /// vezi acel n++ de la linia 38
            (*v)[n-1].L = (struct locatie*)malloc(5*sizeof(struct locatie)); /// alocam vectorul de locatii, 5 a fost ales arbitrar
            if(cnt == 1){ /// avem nume de produs
                strcpy((*v)[n-1].nume,p);
                cnt++;}
            else if(cnt == 2){ /// avem pret
                (*v)[n-1].pret = atoi(p);

                cnt++;}
            else /// intram in sirul de locatii
            {
                int k = 0; /// numaram locatiile ca sa stim exact cat avem
                for(int i = 0 ; i < 5 && p != NULL ; i++) /// pentru 5 vezi linia 46
                {
                    k++;
                    (*v)[n-1].L[i].nume_sector = malloc(strlen(p)); /// alocam dinamic stringul de pe linia 15
                    strcpy((*v)[n-1].L[i].nume_sector,p); /// strcpy(bagi_aici, ce_e_aici);
                    p = strtok(NULL,", "); /// continuam parcurgerea pe subsiruri
                    (*v)[n-1].L[i].gps_x = atoi(p); /// atoi (alpha_to_int = caracter_in_numar_intreg)
                    p = strtok(NULL,", ");
                    (*v)[n-1].L[i].gps_y = atoi(p);
                    p = strtok(NULL,", ");
                }
                (*v)[n-1].nr_loc = k; /// asignam k in membrul nr_loc pt a stii cu exactitate cate locatii avem
            }
            p = strtok(NULL,", "); /// trecem mai departe in subsiruri
            /// atentie, aici facem strtok pt cazurile de la cnt 1 si 2, este evident ca in else-ul final se va termina si p va ramane null si aici
        }
    }
    (*m) = n; /// asignam in parametrul care se intoarce in main cate produse avem
}

void afisare(struct produs *v, int n) /// afisare
{
    for(int i = 0 ; i < n ; i++)
    {
        printf("%s ",v[i].nume);
        printf("%f ",v[i].pret);
        printf("%f ",v[i].distanta_maxima);
        for(int j = 0 ; j < v[i].nr_loc ; j++)
        {
            printf("%s %d %d ",v[i].L[j].nume_sector,v[i].L[j].gps_x,v[i].L[j].gps_y);
        }
        printf("\n");
    }
}
///2
float distanta_euclid(int x1 , int x2, int y1, int y2)
{
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)); /// asta mi ati zis o voi, eu nu le am asa bine cu matematica :))
}

void calcul_distanta(struct produs **v, int n)
{
    for(int i = 0 ; i < n ; i++){
        float maxi = -1;
        for(int j = 0 ; j < (*v)[i].nr_loc - 1 ; j++)
            for(int k = j + 1 ; k < (*v)[i].nr_loc ; k++)
            {
                float d = distanta_euclid((*v)[i].L[j].gps_x,(*v)[i].L[k].gps_x,(*v)[i].L[j].gps_y,(*v)[i].L[k].gps_y);
                        /// folosind functia de la linia 92, calculam distanta pt oricare 2 locatii
                if(d > maxi)
                    maxi = d; /// aici avem maximul dintre oricare 2 locatii
            }
        (*v)[i].distanta_maxima = maxi;}
}

int calcul_duplicat(struct produs v)
{
    int nr = 0;
    int count;
    for(int i = 0 ; i < v.nr_loc - 1 ; i++){
        count = 1;
        for(int j = i + 1 ; j < v.nr_loc ;j++){
            if(strcmp(v.L[i].nume_sector,v.L[j].nume_sector) == 0)
                count++; /// aici aflam daca avem duplicat
            if(count == 2){
            nr++; /// aici crestem numarul de duplicate
            break;}}}
    return nr;
}

int cmp(struct produs a, struct produs b) /// vezi cerinta 3
{
    if(calcul_duplicat(a) < calcul_duplicat(b))
        return -1;
    else if(calcul_duplicat(a) > calcul_duplicat(b))
        return 1;
    else return 0;
}

void sortare(struct produs **v, int n)
{
    qsort((*v),n,sizeof((*v)[0]),cmp); /// vezi qsort.pdf de pe teams
}

///4

/// "ah shit, here we go again"
void adaugare_lista(struct nod **p, struct produs pr) /// adaugam toate produsele din vector in lista simplu inlantuita
{
    struct nod *q = (struct nod*)malloc(sizeof(struct nod)); /// cream nod cu produsul

    /// COPIERE DIN PRODUS IN NOD CARE CONTINE PRODUS

    /// ATENTIE !!!!!! CAND FACETI COPIERE , TREBUIE SA FACETI SI ALOCARE DINAMICA IN COPIE, VEZI LINIILE 156 SI 160

    strcpy(q->info.nume,pr.nume);
    q->info.pret = pr.pret;
    q->info.distanta_maxima = pr.distanta_maxima;
    q->info.nr_loc = pr.nr_loc;
    q->info.L = (struct locatie*)malloc(pr.nr_loc*sizeof(struct locatie));
    for(int i = 0 ; i < pr.nr_loc ; i++)
    {

        q->info.L[i].nume_sector = malloc(strlen(pr.L[i].nume_sector));
        strcpy(q->info.L[i].nume_sector,pr.L[i].nume_sector);
        q->info.L[i].gps_x = pr.L[i].gps_x;
        q->info.L[i].gps_y = pr.L[i].gps_y;
    }
    q->urm = NULL;
    if((*p) == NULL) /// initializare lista (adica practic cand nu e nimic in ea trb sa bagam q-ul ca primul
        (*p) = q;   /// mission accomplished! respect++
    else
    {
        struct nod *u = (struct nod*)malloc(sizeof(struct nod)); /// eticheta de la inceput
        u = (*p);
        while(u -> urm != NULL) /// parcurgem pana la capat
            u = u -> urm; /// aici e gen ca trece mai departe
        u -> urm = q; /// setam noul nod ca fiind urmatorul dupa ultimul
        u = q; /// noul nod devine ultimul (logic)
    }
}

void afisare_lista(struct nod *p)
{
    struct nod *u = (struct nod*)malloc(sizeof(struct nod));
    u = p;
    while(u) /// parcurgere lista total
    {
        printf("%s ",u->info.nume);
        printf("%f ",u->info.pret);
        printf("%f ",u->info.distanta_maxima);
        for(int j = 0 ; j < u->info.nr_loc ; j++)
        {
            printf("%s %d %d ",u->info.L[j].nume_sector,u->info.L[j].gps_x,u->info.L[j].gps_y);
        }
        printf("\n");
        u = u -> urm; /// aici e gen ca trece mai departe
    }
}

void adaugare(struct nod **lista, char* nume_produs, struct produs p)
{
    /// vezi liniile 146-165, basically acelasi lucru
    struct nod *q = (struct nod*)malloc(sizeof(struct nod));
    strcpy(q->info.nume,p.nume);
    q->info.pret = p.pret;
    q->info.distanta_maxima = p.distanta_maxima;
    q->info.nr_loc = p.nr_loc;
    q->info.L = (struct locatie*)malloc(p.nr_loc*sizeof(struct locatie));
    for(int i = 0 ; i < p.nr_loc ; i++)
    {

        q->info.L[i].nume_sector = malloc(strlen(p.L[i].nume_sector));
        strcpy(q->info.L[i].nume_sector,p.L[i].nume_sector);
        q->info.L[i].gps_x = p.L[i].gps_x;
        q->info.L[i].gps_y = p.L[i].gps_y;
    }
    q->urm = NULL;
    struct nod *u = (struct nod*)malloc(sizeof(struct nod));
    u = (*lista);
    int OK = 0, OKend =0; /// ok = inceput secventa consecutiva (dc consecutiva? pentru ca sortam mai inainte :) )
                        /// okend - sfarsit secventa
    while(u -> urm != NULL && OKend == 0){
        if(strcmp(u->info.nume,nume_produs) == 0)
            OK = 1; /// am intrat in secventa chat
        if(OK == 1 && strcmp(u->urm->info.nume,nume_produs) != 0){ /// daca urmatoarea pozitie nu coincide, inseamna ca am ajuns la pozitia unde trb facuta inserarea
            OKend = 1;
            break;}
        u = u -> urm;}
    if(OKend == 1)
        {
            q -> urm = u -> urm; /// legam urmatorul dupa u la q urmator
            u -> urm = q; /// apoi legam q la u urmator si asa am facut inserarea ez pz
        }
    else
        u -> urm = q; /// aici gen daca e la capat forever alone si trb facuta inserare
}

int main()
{
    int n;
    struct produs *v;
    citire(&v,&n);
    calcul_distanta(&v,n);
    ///3
    printf("inainte de sortare: \n");
    afisare(v,n);
    printf("\n");
    sortare(&v,n);
    printf("dupa sortare: \n");
    afisare(v,n);
    printf("\n");
    ///4
    struct nod *p = (struct nod*)malloc(sizeof(struct nod));
    p = NULL;
    for(int i = 0 ; i < n ; i++)
        adaugare_lista(&p,v[i]); /// asa facem adaugare per produs
    printf("lista simplu inlantuita: \n");
    afisare_lista(p);
    printf("\n");
    adaugare(&p, "NvidiaGTX", v[1]); /// am testat cu v[1] ca mi era sila sa declar un produs de la 0
    printf("lista simplu inlantuita dupa adaugare: \n");
    afisare_lista(p); /// gg wp
    printf("\n");
    return 0;
}
