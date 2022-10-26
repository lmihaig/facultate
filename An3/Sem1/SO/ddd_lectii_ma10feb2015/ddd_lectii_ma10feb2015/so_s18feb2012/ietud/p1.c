#include<stdio.h>
#include"fileinfo.i"
int main(int na, char *a[]){
  if(na==2)if(fileinfo(a[1])==-1)perror(a[1]);
  return 0;
}
/* Necesita fisierul "fileinfo.i"
   Utilizare:
   Lansam:
     p1 p1.c
   Pe ecran apare ceva gen:
     -rw-r--r--     dra              293     23/07/2002 p1.c
*/
