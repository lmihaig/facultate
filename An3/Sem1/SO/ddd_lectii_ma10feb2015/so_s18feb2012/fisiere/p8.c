#include<stdio.h>
char citcar(){char c; do scanf("%c",&c);while(c<' '); return c;}
int a; char b[10], x, y;
void main(){
 scanf("%d",&a); x=citcar();
 scanf("%s",b); y=citcar();
 printf("%d %c %s %c\n",a,x,b,y);
}