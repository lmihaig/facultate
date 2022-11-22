#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
int nr;
void h1(){++nr;}
int main(){
  pid_t pt;
  if(fork()){struct sigaction a; sigset_t ms;
             sigemptyset(&ms); a.sa_mask=ms;
             a.sa_handler=h1; sigaction(SIGUSR1,&a,NULL);
             nr=0;
             while(wait(NULL)==-1);
             printf("Tatal a primit %d semnale.\n",nr);
             return 0;
            }
        else{int i;
             sleep(1);
             pt=getppid(); srand(pt); nr=20000+rand()%30001;
             for(i=0; i<nr; ++i)kill(pt, SIGUSR1);
             printf("Fiul a trimis %d semnale.\n",nr);
             return 0;
            }
}
/* Utilizare:
   Lansam:
     p13
   Pe ecran apare ceva gen:
     Fiul a trimis 35872 semnale.
     Tatal a primit 22372 semnale.
*/
