#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
char tubp[11], tuba[10][101], buf[256];
int dp, da[10], na;
void h(int n){close(dp); unlink(tubp); exit(0);}
int main(){int i; sigset_t ms;
   umask(0);	
   sigemptyset(&ms); sigaddset(&ms,SIGPIPE);
   sigprocmask(SIG_SETMASK,&ms,NULL);
   signal(SIGINT,h);
   printf("Dati numele tubului propriu (max.10 car.): ");scanf("%s",tubp);
   mkfifo(tubp,S_IRUSR|S_IWUSR|S_IWGRP|S_IWOTH);
   if(fork()){dp=open(tubp,O_RDONLY);}
         else{dp=open(tubp,O_WRONLY); close(dp); return 1;}
   printf("Specif. tubului propriu este: %s/%s\n",getcwd(buf,255),tubp);
   printf("Dati numarul tuburilor adverse: "); scanf("%d",&na);
   printf("Dati specif.tuburilor adverse (max.10), cate unul pe linie:\n");
   for(i=0; i<na; ++i){scanf("%s",tuba[i]); da[i]=open(tuba[i],O_WRONLY);}
   if(fork()){int offbuf,n;
              strcpy(buf,tubp); strcat(buf,":  "); offbuf=strlen(buf);
      	       while(1){scanf("%s",buf+offbuf);
  	                n=strlen(buf); buf[n]='\n'; ++n;
	                for(i=0; i<na; ++i) write(da[i],buf,n);
                       }
             }
         else{while(1){for(i=0; i<254; ++i){
  		        while(read(dp,buf+i,1)==0);
			if(buf[i]=='\n')break;}
		        buf[i]='\0'; printf("\n%s\n",buf);
	               }
             }
}
/* Utilizare:
   Se lanseaza in paralel de la mai multe terminale diferite (nu
    neaparat de catre acelasi utilizator) - obtinem astfel mai multe procese
    diferite; dam fiecaruia un nume de tub diferit (e bine ca el sa fie
    sugestiv, de exemplu numele persoanei care opereaza: Ion, Ana, etc.);
    fiecare proces va crea un tub cu numele respectiv in directorul sau
    curent, si va afisa specificatorul sau cu cale absoluta (de exemplu:
    /home/ion/Ion); astfel, fiecare proces poate fi identificat cu tubul pe
    care l-a creat.
   Apoi dam fiecarui proces numarul tuburilor (proceselor) cu care vrem sa
    comunice si specificatorii acestora (nu trebuie neaparat sa fie toate
    tuburile create ci doar o parte din ele);
   In continuare are loc talk-ul propriuzis: la fiecare proces operatorul
    introduce linii de text (terminate prin ENTER), iar acestea vor fi
    afisate imediat de toate procesele cu care acesta comunica (operatiile
    fiind efectuate in mod independent); fiecare linie afisata de un proces
    va fi prefixata de numele tubului procesului care a trimis-o - de exemplu
    daca la procesul cu tubul "Ion" operatorul a introdus linia:
                   Ce mai faci ?
    toate celelalte procese vor afisa linia:
                   Ion:  Ce mai faci ?
   In final fiecare proces va fi terminat cu ^c (la terminare el va sterge
    legatura fizica (la un tub) pe care a creat-o); de notat ca daca doar o
    parte dintre procese s-au terminat, celelalte pot continua talk-ul
    nestingherite.
*/
