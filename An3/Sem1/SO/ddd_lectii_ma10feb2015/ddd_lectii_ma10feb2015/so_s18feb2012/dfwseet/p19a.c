#include<stdio.h>
extern char **environ;
void main(){ char **pe;
  for(pe=environ; *pe; ++pe)printf("%s\n",*pe); }
/* Utilizare:
   Lansam:
     p19a
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
