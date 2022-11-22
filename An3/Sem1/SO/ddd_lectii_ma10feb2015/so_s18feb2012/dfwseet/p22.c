#include<stdlib.h>
extern char **environ;
void main(){ int i,j; char buf[100];
  for(i=0; environ[i]; ){
    printf("%s\n",environ[i]);
    for(j=0; environ[i][j]!='='; ++j)buf[j]=environ[i][j]; buf[j]='\0';
    unsetenv(buf);
  }
}
/* Utilizare:
   Lansam:
     p22
   Pe ecran se afisaza environmentul mostenit de proces de la shell (partea
    exportabila a environmentului shell-ului).
*/
