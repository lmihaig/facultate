#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(){
int d;
d=open("f",O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
if(d==5)return;
dup2(d,5); close(d);
write(5,"A",1);
execv("./p27b",NULL);
return 0;
}
/* Necesita programul p27b.
   Utilizare:
   Lansam:
     p27a
   Daca in fisierul "f" se scrie ceva, atunci in final el va contine:
     AB
*/
