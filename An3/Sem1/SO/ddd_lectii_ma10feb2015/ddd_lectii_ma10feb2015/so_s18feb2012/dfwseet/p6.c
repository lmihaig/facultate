#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
void h(int n){
  printf("%d: terminare prin primirea lui SIGALARM.\n",getpid());
  fflush(stdout);
  sleep(3);
  exit(0);}
int main(){
  signal(SIGALRM,h);
  printf("Procesul initial: %d.\n",getpid()); fflush(stdout);
  alarm(1);
  fork();
  sleep(2);
  printf("%d: terminare normala.\n",getpid()); fflush(stdout);
  return 0;
}
/* Utilizare:
   Lansam:
     p6
   Pe ecran se afisaza ceva gen:
     Procesul initial: 21609.
     21609: terminare prin primirea lui SIGALARM.
     21610: terminare normala.
*/
