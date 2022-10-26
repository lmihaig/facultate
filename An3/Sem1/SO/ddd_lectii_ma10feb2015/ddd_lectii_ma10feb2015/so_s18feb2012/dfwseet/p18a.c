#include<stdio.h>
void main(int na, char *a[], char *e[]){ char **pe;
  for(pe=e; *pe; ++pe)printf("%s\n",*pe); }
/* Utilizare:
   Lansam:
     p18a
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
