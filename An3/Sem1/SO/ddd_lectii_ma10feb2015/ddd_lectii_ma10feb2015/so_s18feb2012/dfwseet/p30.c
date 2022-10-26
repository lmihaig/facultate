#include<unistd.h>
int d[2]; char buf[1000];
int main(){int i;
  pipe(d);
  if(fork())
  {close(d[1]); nice(19); buf[read(d[0],buf,1000)]='\0'; printf("%s\n",buf);}
  else
  {close(d[0]); sleep(1); for(i=0;i<1000;++i){write(d[1],"a",1); usleep(1);}}
  return 0;
}
/* Utilizare:
   Lansam de mai multe ori:
     p30
   De fiecare data, dupa o secunda pe ecran se afisaza un sir de "a";
    numarul de "a" afisati nu va fi insa mereu acelasi; de exemplu la trei
    rulari succesive putem obtine:
                   aaaaa
                   aaaa
                   aaaaaaa
*/