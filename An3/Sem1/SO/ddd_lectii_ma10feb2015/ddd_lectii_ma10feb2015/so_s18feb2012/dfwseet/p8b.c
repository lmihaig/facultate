#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(){int d; char s[3];
  d=open("f",O_RDONLY);
  s[2]='\0';
  if(fork()){read(d,&s[0],1); sleep(2); read(d,&s[1],1);
             printf("Tata: %s\n",s); sleep(2);}
      else  {sleep(1); read(d,&s[0],1); sleep(2); read(d,&s[1],1);
             printf("Fiu: %s\n",s);}
  return 0;
}
/* Utilizare:
   Cream un fisier "f" care contine:
     abcd
   Lansam:
     p8b
   Pe ecran se afisaza:
     Tata: ac
     Fiu: bd
*/
