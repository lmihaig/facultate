#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
int d[2]; char a[10000],b[10000],c[10000];
int main(){int i;
for(i=0;i<10000;++i)a[i]='A';
for(i=0;i<10000;++i)b[i]='B';
for(i=0;i<10000;++i)c[i]='\0';
pipe(d);
if(fork()){write(d[1],a,4090); write(d[1],b,1000); wait(NULL);}
     else {sleep(1); i=read(d[0],c,5000); printf("%s %d\n",c,i);}
return 0;
}
/* Utilizare:
   Lansam:
     p31
   Dupa 1 secunda pe ecran se afisaza 4090 de "A", apoi numarul 4090:
*/
