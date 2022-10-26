#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(){int d1, d2; char s[3];
  d1=open("f",O_RDONLY); d2=open("f",O_RDONLY);
  s[2]='\0';
  read(d1,&s,2); printf("%s\n",s);
  read(d2,&s,2); printf("%s\n",s);
  return 0;
}
/* Utilizare:
   Cream un fisier "f" care contine:
     abcd
   Lansam:
     p8a
   Pe ecran se afisaza:
     ab
     ab
*/
