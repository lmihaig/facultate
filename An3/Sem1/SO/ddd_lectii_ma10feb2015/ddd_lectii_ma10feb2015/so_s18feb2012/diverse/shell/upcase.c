#include<stdio.h>
int main(){
  char c;
  for(scanf("%c",&c);!feof(stdin);scanf("%c",&c))
    printf("%c",'a'<=c && c<='z'? c-' ' : c);
  return 0;
}
