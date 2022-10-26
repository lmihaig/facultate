  #include<sys/types.h>
  #include<unistd.h>
  #include<signal.h>
  #include<stdlib.h>
  #include<stdio.h>
  int nr;
  void h1(int n){}
  void h2(int n){printf("Fiul a primit %d semnale.\n",nr); exit(0);}
  int main(){
    pid_t pf;
    if(pf=fork()){int i;
                  sleep(1);
                  srand(getpid());
                  nr=20000+rand()%30001;
                  for(i=0; i<nr; ++i)kill(pf, SIGUSR1);
                  printf("Tatal a trimis %d semnale.\n",nr);
                  kill(pf, SIGINT);
                  sleep(1);
                  return 0;
                 }
             else{struct sigaction a; sigset_t ms;
                  sigemptyset(&ms); a.sa_mask=ms;
                  a.sa_handler=h1; sigaction(SIGUSR1,&a,NULL);
                  a.sa_handler=h2; sigaction(SIGINT,&a,NULL);
                  nr=0;
                  while(1){pause(); ++nr;}
                 }
  }
/* Utilizare:
   Lansam:
     p9a
   Pe ecran apare ceva gen:
     Tatal a trimis 43537 semnale.
     Fiul a primit 23249 semnale.
*/