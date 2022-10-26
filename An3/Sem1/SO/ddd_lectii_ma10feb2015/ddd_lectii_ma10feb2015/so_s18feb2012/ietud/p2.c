#include<stdio.h>
#include"listdir.i"
int main(int na, char *a[]){
  if(na==2)if(listdir(a[1])==-1)perror(a[1]);
  return 0;
}
/* Necesita fisierul "listdir.i" (care la randul lui 
     necesita fisierul "fileinfo.i")
   Utilizare:
   Lansam:
     p2 .
   Pe ecran apare ceva gen:
     drwxr-xr-x     dra            <DIR>     23/07/2002 ./.
     drwxr-xr-x     dra            <DIR>     22/07/2002 ./..
     -rw-r--r--     dra            17839     23/07/2002 ./ietud.txt
     -rw-r--r--     dra             1291     23/07/2002 ./fileinfo.i
     -rw-r--r--     dra              533     23/07/2002 ./listdir.i
     -rw-r--r--     dra              293     23/07/2002 ./p1.c
     -rw-r--r--     dra              858     23/07/2002 ./p2.c
     -rwxr-xr-x     dra            15279     23/07/2002 ./p1
     -rwxr-xr-x     dra            15981     23/07/2002 ./p2
*/
