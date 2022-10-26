#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
FILE *f; char buf[256];
int main(int na, char *a[]){
  if(na!=3){printf("Argumente incorecte.\n"); return 1;}
  mkfifo("tub",S_IRWXU);
  switch(fork()){
    case -1: perror("fork"); return 1;
    case 0: strcpy(buf,a[1]);strcat(buf," > tub");
            system(buf);
            break;
    default:strcpy(buf,a[2]);strcat(buf," < tub");
            system(buf);
            break;
  }
  unlink("tub");
  return 0;
}
/* Necesita programele p33b si p33c.
   Utilizare:
   Lansam:
     p34  p33b  p33c
   Pe ecran se afisaza (la infinit) cate un "A" pe secunda:
     A
     A
     ...
   Toate procesele se termina cu ^c.
*/
