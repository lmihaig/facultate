#include<stdio.h>
void main(int na, char *a[], char *e[]){
  for(;*e;++e)printf("%s\n",*e); }
/* Utilizare:
   Lansam:
     p18b
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
