#include<unistd.h>
#include<stdio.h>
int main(){int i; FILE *f;
  f=fopen("f","wb");
  fprintf(f,"I"); fflush(f);
  if(fork())for(i=0;i<5;++i){fprintf(f,"T"); fflush(f); sleep(1);}
       else for(i=0;i<5;++i){fprintf(f,"F"); fflush(f); sleep(1);}
  return 0;
}
/* Utilizare:
   Lansam:
     p3
   In final fisierul "f" va contine ceva de tipul:
     ITFTFTFTFTF
*/