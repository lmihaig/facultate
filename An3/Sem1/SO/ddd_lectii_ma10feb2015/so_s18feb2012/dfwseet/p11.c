#include<unistd.h>
int main(){
if(fork())while(1);
return 0;
}
/* Utilizare:
   Lansam:
     p11  &
   Dam comanda:
     ps
   Pe ecran se afisaza ceva gen:
      PID TTY          TIME CMD
     7517 pts/7    00:00:00 bash
     7550 pts/7    00:00:05 p11
     7551 pts/7    00:00:00 p11 <defunct>
     7552 pts/7    00:00:00 ps
   Dam comanda:
     kill -KILL 7550
   (de fapt, in loc de "7550" vom da PID-ul aparut mai inainte in dreptul
    lui "p11" care nu este "<defunct>").
*/
