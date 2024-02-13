#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct produs{
    char nume[16];
    float pret;
    char** cod;
};
struct nod{
    char **cod;
    struct nod *urm;
};
///fucntia de alocare a memoriei si de citire
void citire(struct produs** p, int *n){
    int i, j;
    scanf("%d",&(*n));
    *p=(struct produs*)malloc((*n)*sizeof(struct produs));
    for(i=0;i<*n;i++){
        printf("dati numele produsului si pretul: ");
        scanf("%s %f",(*p)[i].nume,&(*p)[i].pret);
        (*p)[i].cod = (char**)malloc(4*sizeof(char*));
        for(j=0;j<4;j++){
            (*p)[i].cod[j]=(char*)malloc(4*sizeof(char));
        }
    }
}
///functia pentru completare a matricii dupa regula data
void completare(struct produs** p, int n){
    int i, j, k;
    char a[4][4];
    for(i=0;i<n;i++){
        for(j=0;j<4;j++)
            for(k=0;k<4;k++){
                if(strlen((*p)[i].nume)<(j*4)+k+1)///verificam daca am depasit lungimea cuvantului si trebuie sa completam restul matricii cu 0
                    a[j][k]='0';
                else
                    a[j][k]=(*p)[i].nume[(j*4)+k];
            }
    ///in matricea a avem matricea formata din fiecare cuvant care acum trebuie rotita si pusa in cod
    for(j=0;j<4;j++)
        for(k=0;k<4;k++){
            (*p)[i].cod[3-k][j]=a[j][k];
        }
    }
}
/*
///comparatorul; comparatorul va sorta crescator dupa pret, iar in cazul in care au acelasi pret, descrescator dupa numarul de zerouri
int cmp(const void *a, const void *b){
    struct produs *produs1=(struct produs*)a;
    struct produs *produs2=(struct produs*)b;
    if(produs1->pret==produs2->pret)
///in caz de egalitate vrem sa sortam descrescator dupa numarul de zerouri. numarul de zerouri este dat de formula 16-strlen(produs->nume), deci pentru
///a sorta descrescator dupa numarul de zerouri, vom sorta crescator dupa numarul de caractere
        return strlen(produs1->nume)-strlen(produs2->nume);
    else
        return produs1->pret-produs2->pret;
}*/

int cmp(struct produs * a, struct produs * b) {
    if(a->pret < b->pret)
        return -1;
    if(a->pret == b->pret)
        if(strlen(a->nume) < strlen(b->nume))
            return -1;
    return 1;
}

///functia care adauga elemente in lista
void creare(struct nod **L, struct produs *p, int n)
{
    int i, j, k;
    (*L)=(struct nod*)malloc(sizeof(struct nod));
    struct nod *u=(struct nod*)malloc(sizeof (struct nod));
    //*L=NULL;
    for(i=0;i<n;i++){
        struct nod *q=(struct nod*)malloc(sizeof(struct nod));
        q->cod = (char**)malloc(4*sizeof(char*));
        for(j=0;j<4;j++){
            q->cod[j]=(char*)malloc(4*sizeof(char));
        }
        for(j=0;j<4;j++)
            for(k=0;k<4;k++)
                q->cod[j][k]=p[i].cod[j][k];
        q->urm=NULL;
        if(i == 0)
        {
            (*L)->cod = (char**)malloc(4*sizeof(char*));
            for(j=0;j<4;j++)
                (*L)->cod[j]=(char*)malloc(4*sizeof(char));
            u->cod = (char**)malloc(4*sizeof(char*));
            for(j=0;j<4;j++){
                u->cod[j]=(char*)malloc(4*sizeof(char));
            }
            for(j=0;j<4;j++)
                for(k=0;k<4;k++){
                    (*L)->cod[j][k]=q->cod[j][k];
                    u->cod[j][k]=q->cod[j][k];
                }
            (*L)->urm=NULL;
            u->urm=NULL;
        }
        else
        {
            if((*L)->urm == NULL)
                (*L)->urm = q;
            u->urm=q;
            u=u->urm;
            u->urm=NULL;
        }
    }
}
///functia de decodificare
int decodificare(struct nod *L, char* produs){
    int i, j, c = 0, nr = 0;
    char produsx[16];
    char a[4][4];
    for(i=0;i<4;i++){
        for(j=3;j>=0;j--){
            if(L->cod[j][i]!='0')
            {
                produsx[4*i+3-j]=L->cod[j][i];
                nr++;
            }
        }
    }
    ///printf("Cuvant dupa decodificare: %s",produsx);
    if(nr != strlen(produs))
        return 0;
    for(i = 0; i < nr; i++)
        if(produs[i] != produsx[i])
            c++;
    if(c == 0)
        return 1;
    else
        return 0;
}

///fuctia care verifica daca un element trebuie eliminat sau nu
void eliminare(struct nod **L, char* produs)
{
    struct nod *q=(struct nod*)malloc(sizeof(struct nod));
    struct nod *t=(struct nod*)malloc(sizeof(struct nod));
    q = (*L);
    while(q->urm != NULL && decodificare(q,produs) == 0)
        q = q->urm;
    if(decodificare(q,produs) == 1)
    {
        q=*L;
        while(q->urm != NULL)
            if(decodificare(q->urm,produs) == 1)
            {
                t=q->urm;
                q->urm=t->urm;
                break;
            }
            else
                q=q->urm;
    }
}

void afisare(struct produs* v, int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("Pret: %f Nume: %s \n",v[i].pret, v[i].nume);
    }
}

void afisare_smechera(struct produs* v, int n)
{
    int i, j, k;
    for(i = 0; i < n; i++)
    {
        printf("Pret: %f Nume: %s \n",v[i].pret, v[i].nume);
        for(k = 0; k < 4; k++)
            {
                for(j = 0; j< 4; j++)
                    printf("%c ",v[i].cod[k][j]);
                printf("\n");
            }
    }
}

int main()
{
    ///1)citire
    int i , j, k;
    printf("dati nr de produse care trebuie inregistrate: ");
    int n;
    struct nod *L;
    struct produs *p;
    citire(&p,&n);
    ///2)completarea matricii
    completare(&p,n);
    afisare_smechera(p,n);
    ///3)sortarea cu qsort
    qsort(p,n,sizeof(struct produs),cmp);
    afisare(p,n);
    ///4)crearea si stergerea din lista
    creare(&L,p,n);
    char produsx[]="mere";
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j< 4; j++)
            printf("%c ",L->cod[i][j]);
        printf("\n");
    }
    struct nod* q = (struct nod*) malloc(sizeof(struct nod));
    q = L;
    while(q->urm != NULL)
    {
        q = q->urm;
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j< 4; j++)
                printf("%c ",q->cod[i][j]);
            printf("\n");
        }
    }
    printf("---------------- \n");
    eliminare(&L,produsx);
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j< 4; j++)
            printf("%c ",L->cod[i][j]);
        printf("\n");
    }
    q = L;
    while(q->urm != NULL)
    {
        q = q->urm;
        for(i = 0; i < 4; i++)
        {
            for(j = 0; j< 4; j++)
                printf("%c ",q->cod[i][j]);
            printf("\n");
        }
    }
    return 0;
}
