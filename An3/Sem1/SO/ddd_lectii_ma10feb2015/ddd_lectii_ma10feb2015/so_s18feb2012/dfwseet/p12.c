#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<stdio.h>

void test(pid_t pid, int status, int untraced){
  int cod;
  if(pid==-1){printf("Eroare sau nu sunt fii.\n"); return;}
  if(pid==0)if(untraced){printf("Fiu activ.\n"); return;}
                   else {printf("Fiu activ sau suspendat.\n"); return;}
  if(WIFEXITED(status)){
     printf("Proc. %d s-a term. cu codul de retur %d\n",
             pid,WEXITSTATUS(status));
     return;}
  if(WIFSIGNALED(status)){
     printf("Proc. %d s-a term. primind semnalul %d\n",
             pid,WTERMSIG(status));
     return;}
  if(WIFSTOPPED(status))
     printf("Proc. %d a fost susp. primind semnalul %d\n",
             pid,WSTOPSIG(status));
}

int main(){
  pid_t p,q; int s;
  q=waitpid(-1, &s, WNOHANG); test(q, s, 0);
  if(!(p=fork())){sleep(10); return 1;}
  sleep(1); q=waitpid(p, &s, WNOHANG); test(q, s, 0);
            q=waitpid(p, &s, WNOHANG|WUNTRACED); test(q, s, 1);
  if(!(p=fork())){raise(SIGSTOP); return 2;}
  sleep(1); q=waitpid(p, &s, WNOHANG|WUNTRACED); test(q, s, 1);
  kill(p, SIGKILL);
  sleep(1); q=waitpid(p, &s, WNOHANG|WUNTRACED); test(q, s, 1);
  q=wait(&s); test(q, s, 0);
  return 0;
}
/* Utilizare:
   Lansam:
     p12
   Pe ecran apare ceva gen:
     Eroare sau nu sunt fii.
     Fiu activ sau suspendat.
     Fiu activ.
     Proc. 3150 a fost susp. primind semnalul 19
     Proc. 3150 s-a term. primind semnalul 9
     Proc. 3149 s-a term. cu codul de retur 1
*/