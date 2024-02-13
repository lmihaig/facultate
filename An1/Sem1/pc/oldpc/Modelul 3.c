#include <stdio.h>

struct tarom
{
    char nume[50];
    char clasa_zbor;
    float greutate_bagaj;
    unsigned int cod : 4;
};

void citire(struct tarom v[101], int n)
{
    int i;
    for(i = 0 ; i < n  ; i++)
    {
        printf("nume: ");
        scanf("%s", v[i].nume);
        getchar();
        printf("clasa zbor: ");
        scanf("%c", &v[i].clasa_zbor);
        printf("greutate bagaj: ");
        scanf("%f", &v[i].greutate_bagaj);
    }
}

void afisare_cu_cod(struct tarom v[101], int n)
{
    int i;
    for( i = 0 ; i < n ; i++)
        printf("nume %s, clasa zbor %c, greutate bagaj %f, cod %d \n",v[i].nume,v[i].clasa_zbor,v[i].greutate_bagaj, v[i].cod);
}

void afisare_fara_cod(struct tarom v[101], int n)
{
    int i;
    for( i = 0 ; i < n ; i++)
        printf("nume %s, clasa zbor %c, greutate bagaj %f \n",v[i].nume,v[i].clasa_zbor,v[i].greutate_bagaj);
}

void codificare(struct tarom v[101], int n)
{
    int x, i, count = 0;
    for(i = 0; i < n; i++)
    {
        count = 0;
        x = v[i].nume[0];
        while(x > 0)
        {
            if(x%2 == 0)
                count++;
            x = x/2;
        }
        v[i].cod = count;
    }
}

int cmp(const void* a, const void* b)
{
    struct tarom* x = (struct tarom*)a;
    struct tarom* y = (struct tarom*)b;
    return ( x->clasa_zbor - y->clasa_zbor );
}

int citire_fisier()
{
    int i;
    char nume[50], clasa;
    float greutate;
    FILE *f = fopen("fisier.txt","r");
    while(fscanf(f,"%s",nume) != EOF)
    {
        fscanf(f," %c", &clasa);
        fscanf(f,"%f", &greutate);
        if(greutate > 30.0)
            printf("nume %s, clasa zbor %c, greutate bagaj %f \n",nume,clasa,greutate);
    }
    fclose(f);
}

int main()
{
    int n;
    int i, j;
    printf("cati calatori: ");
    scanf("%d",&n);
    struct tarom v[101], aux;
    citire(v,n);
    afisare_fara_cod(v,n);
    codificare(v,n);
    afisare_cu_cod(v,n);
    //qsort(v, n, sizeof(struct tarom), cmp);
    for(i = 0; i < n-1; i++)
        for(j = i+1; j <n; j++)
            if(v[i].clasa_zbor > v[j].clasa_zbor)
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
    afisare_cu_cod(v,n);
    citire_fisier();
    return 0;
}
