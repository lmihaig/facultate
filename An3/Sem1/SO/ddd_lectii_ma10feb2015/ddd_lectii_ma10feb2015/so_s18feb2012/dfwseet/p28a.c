#include<unistd.h>
#include<stdio.h>
int main(){printf("A"); fflush(stdout); execv("./p28b",NULL); return 0;}
/* Necesita programul p28b.
   Utilizare:
   Lansam:
     p28a > f
   In final fisierul "f" va contine:
     AB
*/
