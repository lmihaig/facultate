#include <stdio.h>
#include <string.h>  /* pentru strlen */
/*
void afis(char *s, char *nume)
{
    char *p = s;
    printf("Sirul %s este %s si are lungimea %zu\n", nume, s, strlen(s));
    while(*p != '\0')
    {
        printf("(%c) cu valoarea %d\n", *p, *p);
        p++;
    }
    puts("\n-----------------\n");
}


void afis(int x[], int n)  // linia 3
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d ", x[i]);
    puts("");
}
*/

int main()
{
  /*  int v[5] = {0, 1, 2};
    int *p;
    p = v;
    printf("p are sizeof %zu\n", sizeof(p));  // 8, dar formal este sizeof(int*)
    printf("v are sizeof %zu\n", sizeof(v));  // 20, dar formal este sizeof(int) * 5
    afis(v, 5);
    afis(p, 5);

    int a= sizeof(void*);
    printf("%d", a);

    int nr_trotuare, locuri, i, j;
    nr_trotuare = 2;
    locuri = 10;
    _Bool parcare[nr_trotuare][locuri];
    for (i = 0; i < nr_trotuare; ++i)
        for (j = 0; j < locuri; ++j)
        {
            // scanf("%d", &parcare[i][j]);   // linia 12
            parcare[i][j] = ((i+j)%3 == 0);
        }
            

    for (j = 0; j < locuri; ++j, puts(""))
        for (i = 0; i < nr_trotuare; ++i)
            parcare[i][j] ? printf("[%d,%d]\t", i, j) : printf("[   ]\t");
            

    char s1[] = "qwe";  // contine si '\0', are tipul char[4] si poate fi modificat
    afis(s1, "s1");
    char *s2 = "rty";   // contine si '\0', nu poate fi modificat!  https://en.cppreference.com/w/c/language/array_initialization
    afis(s2, "s2");
    char s3[6] = "uio"; // contine si '\0' si poate fi modificat
    afis(s3, "s3");

    for(int i = 0; i < 6; ++i)
        printf("(%c) cu valoarea %d\n", s3[i], s3[i]);
    puts("\n-----------------\n");

    // atentie!!
    char s4[3] = "rew";  // nu contine '\0'
    // afis(s4, "s4");  // !!!
    for(int i = 0; i < 3; ++i)
        printf("(%c) cu valoarea %d\n", s4[i], s4[i]);
    puts("\n-----------------\n");

    char* sir = "un sir\tde\ncaractere";
    printf(sir);
    puts("\n-----------------\n");

    char zi[15];
    puts("\nCe zi este azi?");
    scanf("%14s", zi);
    printf("Am citit %s!\n\n", zi);

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // linia 46

    // scanf se oprese dupa primul spatiu
    // daca vrem sa citim si spatii, folosim fgets
    char propozitie[100];
    printf("Introduceti propozitia: ");
    fgets(propozitie, 100, stdin);
    printf("Am citit: \"");
    fputs(propozitie, stdout);
    puts("\"\nGata!");
    return 0;
*/
 int i, x=0, y=0;

    for(i = 0; i < 15; i++)
        printf("%d %d \n", ++x, y++);
    
    return 0;
}