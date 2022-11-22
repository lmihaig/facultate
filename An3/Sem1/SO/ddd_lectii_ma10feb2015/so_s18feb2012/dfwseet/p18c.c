#include<stdio.h>
void main(int na, char *a[], char *e[]){
  while(*e)printf("%s\n",*e++); }
/* Utilizare:
   Lansam:
     p18c
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
