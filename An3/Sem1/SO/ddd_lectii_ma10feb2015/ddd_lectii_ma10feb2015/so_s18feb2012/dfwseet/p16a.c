#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
int d;
d=open("f",O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
if(d==5)return;
dup2(d,5); close(d);
write(5,"A",1);
system("./p16b");
return 0;
}
/* Necestia programul p16b.
   Utilizare:
   Lansam:
     p16a
   In final fisierul "f" va contine:
     AB
*/

