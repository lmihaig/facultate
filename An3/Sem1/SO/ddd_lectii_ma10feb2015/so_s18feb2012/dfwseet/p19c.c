#include<stdio.h>
extern char **environ;
void main(){
  while(*environ)printf("%s\n",*environ++); }
/* Utilizare:
   Lansam:
     p19c
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
