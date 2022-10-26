/* joc x si 0 single si in retea cu mmap; ultima modificare: ma-16-apr-02 */
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<curses.h>
#include<stdio.h>

char (*t)[3]; struct tabla{char t[4][3];} st; 
  /*pana la t[2][2] e tabla; t[3][0]=cine e la mutare */
int y,x,j,i;
char eu,tu;

int castigator(char (*t)[3], char c, int poz[][2]){
  static int p[8][3][2]={
     {{0,0},{0,1},{0,2}},{{1,0},{1,1},{1,2}},{{2,0},{2,1},{2,2}},
     {{0,0},{1,0},{2,0}},{{0,1},{1,1},{2,1}},{{0,2},{1,2},{2,2}},
     {{0,0},{1,1},{2,2}},{{0,2},{1,1},{2,0}}
  }; 
  int k,l,j1,i1;
  for(k=0;k<8;++k)if(
   t[p[k][0][0]][p[k][0][1]]==c &&
   t[p[k][1][0]][p[k][1][1]]==c &&
   t[p[k][2][0]][p[k][2][1]]==c
  ){
   for(l=0;l<3;++l){poz[l][0]=p[k][l][0];poz[l][1]=p[k][l][1];}
   return 1;  /* c este castigator */
  } 
  k=1; for(j1=0;j1<3;++j1)for(i1=0;i1<3;++i1)if(t[j1][i1]==' ')k=0;
  if(k) return -1; /* tabla plina (remiza sau celalalt e castigator) */ 
  return 0; /* partida nu s-a terminat */ 
}

int prob(double p){return rand()/(RAND_MAX+1.) < p;}
double mutarenoua(struct tabla st, char eu, int *j, int *i){
  char tu; int j1,i1,j2,i2,jmin,imin,k,kmin; int poz[3][2];
  if(eu=='x')tu='0'; else tu='x'; 
  for(j1=0;j1<3;++j1)for(i1=0;i1<3;++i1)if(st.t[j1][i1]==' '){
    st.t[j1][i1]=eu;
    if(castigator(st.t,eu,poz)==1){*j=j1; *i=i1; return 1;} 
    st.t[j1][i1]=' ';
  }
  for(j1=0;j1<3;++j1)for(i1=0;i1<3;++i1)if(st.t[j1][i1]==' '){
    st.t[j1][i1]=eu;
    if(castigator(st.t,eu,poz)==-1){*j=j1; *i=i1; return 0;} 
    st.t[j1][i1]=' ';
  }
  kmin=2;  
  for(j1=0;j1<3;++j1)for(i1=0;i1<3;++i1)if(st.t[j1][i1]==' '){
    st.t[j1][i1]=eu;
    k=mutarenoua(st,tu,&j2,&i2);
    if(k<kmin || (k==kmin && prob(0.5))){kmin=k; jmin=j1; imin=i1;}
    st.t[j1][i1]=' ';
  }  
  *j=jmin; *i=imin; return -kmin;
}   

int main(){
  int d,tip,continua,k,l,j1,i1,y1,x1,c,poz[3][2]; 
  char nf[]="XXXXXX",buf[70],cine; 
  printf("Tipul de joc (0=singur, 1=initiere dublu, 2=conectare la dublu): ");
  do scanf("%d",&tip); while(tip !=0 && tip !=1 && tip !=2);
  switch(tip){
  case 0: 
    t=st.t;
    for(j1=0;j1<4;++j1)for(i1=0;i1<3;++i1)t[j1][i1]=' ';
    printf("Semnul propriu (x sau 0): ");
    do scanf("%c",&eu); while(eu !='x' && eu !='0');
    if(eu=='x') tu='0'; else tu='x';
    printf("Primul la mutare (x sau 0): ");
    do scanf("%c",&cine); while(cine !='x' && cine !='0');
    t[3][0]=cine;
    srand(time(NULL));
    break;
  case 1:
    if((d=mkstemp(nf))==-1)return 1; 
    if(fchmod(d,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)==-1)
      {unlink(nf); return 1;}
    write(d,"            ",12);
    t=(char(*)[3])mmap(0,12,PROT_READ | PROT_WRITE, MAP_SHARED, d, (long)0);
    if(t==NULL){unlink(nf); return 1;}
    printf("Semnul propriu (x sau 0): ");
    do scanf("%c",&eu); while(eu !='x' && eu !='0');
    if(eu=='x') tu='0'; else tu='x';
    t[3][0]=eu;
    break;
  case 2: 
    printf("Fisierul tabla: "); scanf("%s",nf);
    if((d=open(nf,O_RDWR,0))==-1)return 1;
    t=(char(*)[3])mmap(0,12,PROT_READ | PROT_WRITE, MAP_SHARED, d, (long)0);
    if(t==NULL)return 1;
    if(t[3][0]=='x'){eu='0';tu='x';}else{eu='x';tu='0';}
    printf("Semnul propriu: %c\n",eu);  
  } 

  initscr(); cbreak();  noecho(); 
  nodelay(stdscr,FALSE); keypad(stdscr,TRUE);
  switch(tip){ 
   case 1: mvprintw(1,1,"Fisierul tabla este: %s/%s",getcwd(buf,70),nf);break;
   case 2: mvprintw(1,1,"Fisierul tabla este: %s",nf);
  }
  mvprintw(2,1,"Semnul propriu: %c",eu);
  mvprintw(3,1,"La mutare este: "); mvprintw(3,17,"%c",t[3][0]);
  mvprintw(2,40,"Mutare: stanga, dreapta, sus, jos");
  mvprintw(3,40,"Marcare: space");
 mvhline(5,29,0,19);mvhline(9,29,0,19);mvhline(13,29,0,19);mvhline(17,29,0,19);
 mvvline(6,29,0,11);mvvline(6,35,0,11);mvvline(6,41,0,11);mvvline(6,47,0,11);
  y=7; x=32; j=0, i=0; curs_set(0); move(y,x); continua=1;
  
  do{
     cine=t[3][0]; /* trebuie cunoscut inainte de afisarea tablei */
     for(j1=0,y1=7;j1<3;++j1,y1+=4) for(i1=0,x1=32;i1<3;++i1,x1+=6)
       mvaddch(y1,x1,t[j1][i1]);
     mvprintw(3,17,"%c",cine);  
     refresh(); 
     if(cine==eu){
       k=castigator(t,tu,poz);
       if(k==1){ 
         attron(A_BLINK);
         for(l=0;l<3;++l)mvaddch(7+4*poz[l][0],32+6*poz[l][1],tu);
         attroff(A_BLINK);
         mvprintw(20,1,"Ati pierdut !"); 
         refresh(); 
         beep(); usleep(200000); beep(); 
         break;
       }else if(k==-1){
         mvprintw(20,1,"Remiza !"); refresh();
         beep(); usleep(200000); beep(); 
         break;            
       }
       beep();
       curs_set(1); move(y,x);
       do{switch(c=getch()){
        case KEY_LEFT: if(x>32){x-=6; --i; move(y,x);}break;
        case KEY_RIGHT: if(x<44){x+=6; ++i; move(y,x);}break;
        case KEY_UP: if(y>7){y-=4; --j; move(y,x);}break;
        case KEY_DOWN: if(y<15){y+=4; ++j; move(y,x);}break;
        case ' ': if(t[j][i]==' '){
                   t[j][i]=eu; 
                   mvaddch(y,x,eu); refresh(); move(y,x);
                   k=castigator(t,eu,poz);
                   if(k==1){
                     attron(A_BLINK);
                     for(l=0;l<3;++l)mvaddch(7+4*poz[l][0],32+6*poz[l][1],eu);
                     attroff(A_BLINK);
                     mvprintw(20,1,"Ati castigat !"); 
                     refresh();
                     beep(); usleep(200000); beep();
                     continua=0;
                   }else if(k==-1){
                     mvprintw(20,1,"Remiza !"); refresh();
                     beep(); usleep(200000); beep(); 
                     continua=0;
                   } 
                   t[3][0]=tu; /* asta se pune DUPA testele "castigator" */
                 }else c='a'; /* mutare gresita */ 
       }
       redrawwin(stdscr); /* fara asta, pe unele termiale virtuale nu merge */
       }while(c!=' ');
       curs_set(0);
     }else /* cine==tu */ if(tip==0){
       mutarenoua(st,tu,&j1,&i1);
       t[j1][i1]=tu;
       t[3][0]=eu;     
     } 
   }while(continua);
  
  endwin(); 
  if(tip==1)unlink(nf); 
  return 0;
}


/* Date si rutine utile (man ncurses):
programele trebuie compilate cu -lncurses:
  cc -lncurses .....
stdscr = fereastra implicita, avand dimensiunea terminalului (de tip WINDOW*);
WINDOW* initscr(); --> prima rutina apelata; initializeaza rutinele ncurses;
int cbreak(); in nocbreak(); --> caracterele tastate sunt accesibile imediat 
  (fara buffer si Enter) / respectiv linia este accesibila dupa tastatarea 
  Enter; returneaza OK,ERR;
int refresh(); --> goleste bufferul ferestrei pe terminalul fizic; returneaza:
  ERR = eroare, OK (sau alceva !=ERR) = succes;
int redrawwin(WINDOW* win); --> repara fereastra afisata, daca imaginea a fost
  corupta de un eveniment extern (ex: de catre un alt program, cum ar fi un 
  write ...); returneaza: OK,ERR; 
int erase(); --> sterge continutul ferestrei (pune blankuri); returneaza: OK; 
int curs_set(int vizibilitate); --> seteaza vizibilitatea cursorului de la 0
  (invizibil) la 2;
int printw(char* format, ...); --> afisare cu format in fereastra; ret: OK,ERR;
int mvprintw(int y, int x, char* format, ...); --> la fel, la niste coord.;
int scanw(char* format,...); int mvscanv(int y, int x, char* format, ...); -->
  ca mai sus, dar e citire cu format;
int addch(chtype ch); --> afisare un caracter in fereastra si avansare cursor;
  returneaza: OK, ERR;
int mvaddch(int y, int x, chtype ch); --> la fel, la niste coordonate;  
int getch(); --> citesc un caracter si-l returneaza; 
int mvgetch(int y, int x); --> la fel, dar asteapta la niste coordonate;
int ungetch(int ch); --> plaseaza ch (inapoi in) coada de intrare, pentru a
  fi returnat la urmatorul getch; obs: exista o singura coada pentru toate
  ferestrele; returneaza: OK,ERR; e utila pentru a testa caracterele
  ulterioare celui curent prelucrat cand luam decizii privind destinatia 
  acestuia;
int flushinp(); --> elimina caracterele tastate si necitite inca de program;
  returneaza; OK; e utila pentru eliminarea caracterelor parazite ramase in
  bufferul de intrare;   
int getstr(char *str); --> citeste un sir pana la Enter (exclusiv) si-l pune 
  in *str; returneaza: OK, ERR;
int mvgetstr(int y, int x, char* str); --> la fel, la niste coordonate;   
int echo(); int noecho(); --> (mv)getch e cu ecou sau fara; returneaza: OK,ERR;
int nodelay(WINDOW* win, bool bf); --> bf=TRUE: getch nu astepta daca nu am 
  tastat nimic si returneaza ERR; bf=FALSE: asteapta pana tastam;
int halfdelay(int zecimi); --> spre deosebire de nodelay, daca nu am tastat 
  nimic getch asteapta zecimi zecimi de secunda, apoi returneaza ERR;
int notimeout(WINDOW* win, bool bf); --> bf=FALSE: la citirea unui ESC, getch
  asteapta o mica perioada de timp dupa fiecare caracter citit, pentru a vedea
  daca ESC a fost singur (generat de tasta ESC) sau inceputul unsei secvente
  escape (generata de ex. o tasta functionala), caz in care trebuie vazut si
  cate caractere sunt in secventa (cand timpul scurs dupa un caracter a depasit
  perioada cronometrata se incheie interpretarea secventei escape si se 
  returneaza rezultatul - vezi si functia keypad); bf=TRUE: getch nu mai
  asteapta; returneaza: OK,ERR;
int keypad(WINDOW* win, bool bf); --> bf=TRUE: secventele de caractere emise de
  tastele functionale (secventele escape) sunt returnate de getch ca o singura 
  valoare (ex: KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_ENTER); in cazul
  keypad(...,TRUE) si notimeout(...,FALSE) un sir de taste sageata de exemplu
  este prelucrat mai lent (cursorul se misca mai greu), datorita perioadelor
  de asteptare la interpretarea fiecarei secvente escape; bf=FALSE: caracterele
  din secventa escape sunt emise separat; returneaza: OK,ERR;
  Obs: daca o secventa escape nu este procesata complet (de ex. timpul intre 
  doua caractere componente este prea mare si getch nu mai asteapta), programul
  poate crede ca am tastat ESCAPE si apoi niste caractere obisnuite, pe care le
  afisaza pe ecran - de ex. la sageata dreapta afisaza: [C 
int attron(int attrs); int attroff(int attrs); in continuare, in fereastra
  caracterele scrise cu (mv)addch, (mv)printw vor avea / nu vor avea atributele
  attr; exemple de attr: A_NORMAL (afisare normala), A_UNDERLINE (caractere
  subliniate), A_REVERSE (caractere pe video invers), A_BLINK (caractere
  clipitoare);
int delch(); --> sterge caracterul de pe cursor; restul de pe aceeasi linie
  se deplaseaza spre stanga; returneaza: OK,ERR;
int insdelln(int n); --> insereaza n linii deasupra celei curente (n>0) sau 
  sterge n linii (n<0) incepand cu cea curenta; restul liniilor sunt deplasate;
  returneaza: OK,ERR;    
int insch(); int mvinsch(int y, int x); --> insereaza ch la pozitia curenta /
  respectiv y,x, deplasand restul caracterelor spre dreapta; ret: OK,ERR;
int insstr(const char* str); int mvinsstr(int y, int x, const char *str); -->
  ca mai sus, dar insereaza un string;  
int scrollok(WINDOW *win, bool bf); --> daca ulterior incercam sa iesim cu
  cursorul din fereastra, continutul defileaza (bf=TRUE) sau nu (bf=FALSE); 
int scrl(int n); --> defileaza fereastra n linii (in sus pt. n>0 sau jos pt.
  n<0); returneaza OK,ERR; ca sa mearga trebuie dat scrollok(TRUE);  
int beep(); --> scoate un sunet scurt; returneaza: OK,ERR;      
int move(int y, int x); --> muta cursorul; returneaza: OK, ERR;
void getyx(WINDOW* win, int y, int x); --> macro care pune in y,x pozitia
  curenta a cursorului (fiid macro, x, y sunt practic prin referinta);
void getmaxyx(WINDOW* win, int y, int x); --> macro care pune in y,x 
  dimensiunile ferestrei (fiind macro x, y sunt practic prin referinta);
  coordonatele utile pe ecran sunt 0,...,y-1 si 0,...,x-1;
int resizeterm(int nrlinii, int nrcoloane); --> redimensioneaza fereastra 
  standard si cea curenta (de exemplu erau intr-o consola xwindows care a 
  fost redimensionata cu mouse-ul) 
int border(chtype l, chtype r, chtype t, chtype b, 
           chtype tl, chtype tr, chtype bl, chtype br); --> deseneaza un 
  dreptunghi in jurul ferestrei, format din caractere 
  l (pe stanga), tl (coltul sus stanga), etc;
  parametrii pot fi 0 si atunci caracterele respective sunt respectiv:
  ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
  ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER;
  returneaza: OK,ERR;
int hline(chtype ch, int n); int mvhline(int y, int x, chtype ch, int n)--> 
  deseneaza linie orizontala de la cursor (respectiv de la pozitia (y,x)) 
  spre dreapta pana iese din fereastra sau s-au scris n caractere, formata 
  din ch; daca ch=0, se foloseste ACS_HLINE; cursorul ramane pe loc; 
  returneaza OK,ERR;
int vline(chtype ch, int n); int mvvline(int y, int x, chtype ch, int n)--> 
  la fel pe verticala in jos, iar ch=0 inseamna ACS_VLINE;
int endwin(); --> revenire in mod tty; se apeleaza inainte de iesirea din mod
  ncurses;
int isendwin(); --> returneaza TRUE daca am apelat endwin fara refresh si FALSE
  altfel;
*/
