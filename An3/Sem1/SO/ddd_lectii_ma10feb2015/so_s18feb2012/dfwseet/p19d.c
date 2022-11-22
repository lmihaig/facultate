#include<stdio.h>
extern char **environ;
void main(){int i;
  for(i=0;environ[i];++i)printf("%s\n",environ[i]); }
/* Utilizare:
   Lansam:
     p19d
   Pe ecran se afisaza environmentul procesului lansat, sub forma unor siruri
    de forma "variabila=valoare"
*/
