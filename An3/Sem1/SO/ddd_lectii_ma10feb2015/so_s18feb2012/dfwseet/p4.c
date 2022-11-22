#include<unistd.h>
#include<stdio.h>
int main(){int i; FILE *f;
  f=fopen("f","wb");
  fprintf(f,"I"); fflush(f);
  if(fork())for(i=0;i<5;++i){fprintf(f,"T"); fflush(f); sleep(1);}
       else {sleep(6);
            for(i=0;i<5;++i){fprintf(f,"F"); fflush(f); sleep(1);}}
  return 0;
}
/* Utilizare:
   Lansam:
     p4
   In final fisierul "f" va contine ceva de tipul:
     ITTTTTFFFFF
   (Atentie: prompterul apare dupa 5 secunde, dar fisierul trebuie citit
    dupa cel putin 11 secunde, altfel vom gasi in el mai putin de cinci
    "F" !)
*/