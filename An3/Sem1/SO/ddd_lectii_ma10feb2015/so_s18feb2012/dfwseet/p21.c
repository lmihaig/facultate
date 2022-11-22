#include<stdio.h>
extern char **environ;
void main(int na, char *a[], char *e[]){int i;
   for(i=0; e[i]; ++i)printf("%s\n",e[i]);
   for(i=0; environ[i]; ++i)printf("%s\n",environ[i]);
   printf("%p   %p   %d\n", e, environ, e==environ);
   unsetenv("PATH");
   printf("%p   %p   %d\n", e, environ, e==environ);
   putenv("XXXXXXXX=123");
   printf("%p   %p   %d\n", e, environ, e==environ);
   putenv("yyyyyyyy=abc");
   printf("%p   %p   %d\n", e, environ, e==environ);
   unsetenv("XXXXXXXX");
   printf("%p   %p   %d\n", e, environ, e==environ);
   unsetenv("TERM");
   printf("%p   %p   %d\n", e, environ, e==environ);
   for(i=0; e[i]; ++i)printf("%s\n",e[i]);
   for(i=0; environ[i]; ++i)printf("%s\n",environ[i]);
 }
/* Utilizare:
   Lansam:
     p21
   Pe ecran se afisaza ceva gen:
  <o afisare a environmentului mostenit de la shell (partea exportabila a
   environmentului shell-ului)>
  <o alta afisare a environmentului, identica cu prima>
                   0xbffffc2c   0xbffffc2c   1
                   0xbffffc2c   0xbffffc2c   1
                   0xbffffc2c   0x80498d8   0
                   0xbffffc2c   0x80498d8   0
                   0xbffffc2c   0x80498d8   0
                   0xbffffc2c   0x80498d8   0
  <o afisare a environmentului, in care nu apar "yyyyyyyy" si "PATH", dar
   apare "TERM">
  <o afisare a environmentului in care apare "yyyyyyyy" si nu apar "PARH"
   si "TERM">
*/
