#include<stdio.h>
union {int n; char c[4];} r;
void main(){
 printf("Dati primele doua caractere: "); scanf("%c%c",&r.c[0],&r.c[1]);
 r.c[2]=0; r.c[3]=0;
 printf("Nr. corespunzator este: %d\n",r.n);
 printf("Dati un intreg: "); scanf("%d",&r.n);
 printf("Reprezentarea este: %c%c%c%c\n",r.c[0],r.c[1],r.c[2],r.c[3]);
}