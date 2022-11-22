#include<stdio.h>
#include<unistd.h>
int main(int na, char *a[], char *e[]){
  int i;
  char *arg[]={"./p25b","a","b",NULL}, *env[]={"x=1",NULL};
  printf("Proces PID=%d, PPID=%d\n",getpid(),getppid());
  printf("Argumente:\n"); for(i=0; i<na; ++i)printf("  %s\n",a[i]);
  printf("Environment:\n"); for(i=0; e[i]; ++i)printf("  %s\n",e[i]);
  execve("./p25b", arg, env);
  return 0;
}
/* Necesita programul p25b.
   Utilizare:
   Lansam:
     p25a
   Pe ecran se afisaza ceva gen:
     Proces PID=19677, PPID=19280
     Argumente:
       p25a
     Environment:
       <un environment mare, mostenit de la shell>
     Proces PID=19677, PPID=19280
     Argumente:
       ./p25b
       a
       b
     Environment:
       x=1
*/
