#include<stdio.h>
#include<unistd.h>
int main(int na, char *a[], char *e[]){
  int i;
  printf("Proces PID=%d, PPID=%d\n",getpid(),getppid());
  printf("Argumente:\n"); for(i=0; i<na; ++i)printf("  %s\n",a[i]);
  printf("Environment:\n"); for(i=0; e[i]; ++i)printf("  %s\n",e[i]);
}
/* Program auxiliar pentru "p25a"; nu se lanseaza direct */