#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
char tubp[11], tuba[10][101], buf[256], c;
FILE *fp, *fa[10]; int na;
void h(int n){fclose(fp); unlink(tubp); exit(0);}
int main(){int i; sigset_t ms;
   umask(0);	
   sigemptyset(&ms); sigaddset(&ms,SIGPIPE);
   sigprocmask(SIG_SETMASK,&ms,NULL);
   signal(SIGINT,h);
   printf("Dati numele tubului propriu (max.10 car.): ");scanf("%s",tubp);
   mkfifo(tubp,S_IRUSR|S_IWUSR|S_IWGRP|S_IWOTH);
   if(fork()){fp=fopen(tubp,"rb");}
         else{fp=fopen(tubp,"wb"); fclose(fp); return 1;}
   printf("Specif. tubului propriu este: %s/%s\n",getcwd(buf,255),tubp);
   printf("Dati numarul tuburilor adverse: "); scanf("%d",&na);
   printf("Dati specif.tuburilor adverse (max.10), cate unul pe linie:\n");
   for(i=0; i<na; ++i){scanf("%s",tuba[i]); fa[i]=fopen(tuba[i],"wb");}
   if(fork()){int offbuf;
              strcpy(buf,tubp); strcat(buf,":  "); offbuf=strlen(buf);
              while(1){scanf("%s",buf+offbuf); strcat(buf,"\n");
  	                for(i=0; i<na; ++i){fprintf(fa[i],"%s",buf);
		                    fflush(fa[i]);}
                      }
             }
        else{while(1){while(!fgets(buf,255,fp));
		        printf("\n%s",buf);
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
