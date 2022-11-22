#include<unistd.h>
#include<stdio.h>
int main(){int i;
  sleep(1);
  printf("I"); fflush(stdout);
  if(fork())for(i=0;i<5;++i){printf("T"); fflush(stdout); sleep(1);}
       else {sleep(6);
             for(i=0;i<5;++i){printf("F"); fflush(stdout); sleep(1);}}
  return 0;
}
/* Utilizari posibile:
   - Setam:
       stty tostop
     Lansam:
       p5
     Pe ecran apare:
       ITTTTTbash$
     ("bash$" e prompterul);
   - Setam:
       stty -tostop
     Lansam:
       p5
     Pe ecran apare:
       ITTTTTbash$ FFFFF
     ("bash$" e prompterul);
   - Setam:
       stty -tostop
     Lansam:
       p5  &
     Pe ecran apare:
       bash$ ITTTTTFFFFF
     ("bash$" e prompterul);
   - Lansam:
       p5 > f
     In final fisierul "f" va contine:
       ITTTTTFFFFF
*/
