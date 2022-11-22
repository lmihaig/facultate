#include<stdlib.h>
#include<unistd.h>
extern char **environ;
void afisenv(){int i;
 for(i=0; environ[i]; ++i)printf("  %s\n",environ[i]);
}
int main(int na, char *a[]){
  int i,j; char buf[100];
  if(na==2){printf("Fiul cu system are ca env.:\n"); afisenv(); exit(0);}
  for(i=0; environ[i]; ){
    for(j=0; environ[i][j]!='='; ++j)buf[j]=environ[i][j]; buf[j]='\0';
    unsetenv(buf);
  }
 printf("Env. initial:\n"); afisenv();
 putenv("x1=10");printf("Am ad.x1=10; env. rezultat este:\n"); afisenv();
 putenv("x1=20");printf("Am modif.x1=20; env. rezultat este:\n");afisenv();
 putenv("x2=50");printf("Am ad.x2=50; env. rezultat este:\n"); afisenv();
 unsetenv("x1");printf("Am elim.x1; env. rezultat este:\n"); afisenv();
 if(!fork()){printf("Fiul cu fork are ca env.:\n"); afisenv(); exit(0);}
 wait(NULL);
 system("./p23 1");
 return 0;
}
/* Utilizare:
   Lansam:
     p23
   Pe ecran se afisaza ceva gen:
     Env. initial:
     Am ad.x1=10; env. rezultat este:
       x1=10
     Am modif.x1=20; env. rezultat este:
       x1=20
     Am ad.x2=50; env. rezultat este:
       x1=20
       x2=50
     Am elim.x1; env. rezultat este:
       x2=50
     Fiul cu fork are ca env.:
       x2=50
     Fiul cu system are ca env.:
       x2=50
       PWD=/home/funinf/dra/work
       HOSTNAME=moisil.cs.unibuc.ro
       MACHTYPE=i586-mandrake-linux-gnu
       SHLVL=1
       SHELL=/bin/bash
       HOSTTYPE=i586
       OSTYPE=linux-gnu
       TERM=dumb
       PATH=/usr/local/bin:/bin:/usr/bin
       _=./p23
*/
