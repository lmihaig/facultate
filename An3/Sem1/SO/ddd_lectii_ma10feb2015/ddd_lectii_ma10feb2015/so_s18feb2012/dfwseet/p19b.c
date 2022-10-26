#include<stdio.h>
extern char **environ;
void main(){
  for(;*environ;++environ)printf("%s\n",*environ); }
/* Utilizare:
   Lansam:
     p19b
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
