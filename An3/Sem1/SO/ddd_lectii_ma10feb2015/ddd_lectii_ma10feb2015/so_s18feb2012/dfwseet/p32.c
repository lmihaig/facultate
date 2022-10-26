#include<unistd.h>
#include<stdio.h>
int d[2]; char c; FILE *f,*g;
int main(){
  pipe(d); f=fdopen(d[0],"rb"); g=fdopen(d[1],"wb");
  write(d[1],"a",1);
  fscanf(f,"%c",&c);
  printf("%c\n",c);  /* pe ecran apare "a" */
  fprintf(g,"a");    /* "a" ajunge in buff. lui "*g", nu in tub */
  fscanf(f,"%c",&c); /* blocaj: citire din tub vid, dar cu scriitori */
  printf("%c\n",c);
  return 0;
}
/* Utilizare:
   Lansam:
     p32
   Pe ecran se afisaza:
     a
   Apoi se blocheaza.
   Terminam procesul cu ^c.
*/
