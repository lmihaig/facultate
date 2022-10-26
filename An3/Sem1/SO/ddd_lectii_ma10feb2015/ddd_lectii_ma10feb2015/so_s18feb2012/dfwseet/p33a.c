#include<unistd.h>
int d[2]; char *anou[2];
int main(int na, char *a[]){
  if(na!=3){printf("Nr. gresit de argumente.\n"); return 1;}
  if(pipe(d)==-1){perror("pipe"); return 1;}
  switch(fork()){
    case -1: perror("fork"); return 1;
    case 0: close(1); dup(d[1]);  /* 1 <=>  d[1] */
            close(d[0]); close(d[1]);
	    anou[0]=a[1]; anou[1]=NULL;
            execv(a[1],anou);
            perror("execv"); return 1;
    default:close(0); dup(d[0]);  /* 0  <=>  d[0] */
           close(d[0]); close(d[1]);
	    anou[0]=a[2]; anou[1]=NULL;
            execv(a[2],anou);
            perror("execv"); return 1;
  }
  return 0;
}
/* Necesita programele p33b si p33c.
   Utilizare:
   Lansam:
     p33a  p33b  p33c
   Pe ecran se afisaza (la infinit) cate un "A" pe secunda:
     A
     A
     ...
   Toate procesele se termina cu ^c.
*/
