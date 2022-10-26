#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(){int d,i;
  d=open("f",O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
  write(d,"I",1);
  if(fork())for(i=0;i<5;++i){write(d,"T",1); sleep(1);}
       else for(i=0;i<5;++i){write(d,"F",1); sleep(1);}
  return 0;
}
/* Utilizare:
   Lansam:
     p2
   In final fisierul "f" va contine ceva de tipul:
     ITFTFTFTFTF
*/
