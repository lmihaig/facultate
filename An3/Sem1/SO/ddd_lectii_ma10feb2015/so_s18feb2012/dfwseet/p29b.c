#include<stdio.h>
int main(int na, char *a[], char *e[]){
  int i;
  printf("Program p29b:\n");
  printf("\nArgumente:\n"); for(i=0; i<na; ++i)printf("%s\n",a[i]);
  printf("\nEnvironment:\n"); for(i=0; e[i]; ++i)printf("%s\n",e[i]);
}
/* Program auxiliar pentru "p29a"; nu se lanseaza direct */
