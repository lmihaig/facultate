#include<stdio.h>
#include<stdlib.h>
void main(int np, char *p[]){
 int s=0,i;
 for(i=1;i<np;++i)s+=atoi(p[i]);  
 printf("%f\n",s/(float)(np-1));
}