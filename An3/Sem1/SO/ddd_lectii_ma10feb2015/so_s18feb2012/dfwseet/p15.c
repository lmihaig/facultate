#include<stdlib.h>
void main(){system("ps -l");}
/* Utilizare:
   Lansam:
     p15
   Pe ecran se afisaza ceva gen:
  F S   UID   PID  PPID  C PRI  NI ADDR    SZ WCHAN  TTY          TIME CMD
000 S   520 18691 18689  0  70   0    -   523 wait4  pts/6    00:00:00 bash
000 S   520 19231 18691  0  75   0    -   254 wait4  pts/6    00:00:00 p15
000 R   520 19232 19231  0  77   0    -   603 -      pts/6    00:00:00 ps
*/
