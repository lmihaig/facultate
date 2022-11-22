#include<stdio.h>
void main(int na, char *a[], char *e[]){int i;
  for(i=0;e[i];++i)printf("%s\n",e[i]); }
/* Utilizare:
   Lansam:
     p18d
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
