// ilustrare proprietati referinte,
// contoare declarate in for

#include<stdio.h>

void swap1(int *a, int *b){
  int c;
  c=*a; *a=*b; *b=c;
}

void swap2(int &a, int &b){
  int c;
  c=a; a=b; b=c;
}

void main(){

 int a;
 int &r=a;
 r=1; /* a=1; */
 printf("%d\n",a);

 int v[]={1,2,3}, n=sizeof(v)/sizeof(int);
 for(int i=0;i<n;++i){
   int &s=v[i];
   printf("%d ",s);
 }
 printf("\n");

 int x=1,y=2;
 swap1(&x,&y); printf("%d %d\n",x,y);
 swap2(x,y);   printf("%d %d\n",x,y);
}
