/* test de reactualizare automata a dimensiunilor ferestrei */
/* se lanseaza la un terminal virtual (ex: xterm), 
   care se reajusteaza din cand in cand cu mouse-ul; 
   se plimba cursorul cu sageti; 
   se iese cu ESC */
/* ultima modificare: s-13-apr-2002 */

#include<curses.h>

int main(){
  int yc,xc,y,x,ymax,xmax,ym,xm,starty,startx,dimy,dimx,midy,midx,
      continua,c; 

  initscr(); cbreak(); noecho(); 
  nodelay(stdscr,TRUE); /* daca pun false, nu mai reactioneaza prompt la 
                           redimensionarea ferestrei */ 
  keypad(stdscr,TRUE); notimeout(stdscr,FALSE);
  ymax=xmax=starty=startx=dimy=dimx=midy=midx=0;
  yc=xc=0; move(yc,xc);
  ym=ymax-1; xm=xmax-1;
  continua=1;
  do{
    refresh(); /* altfel nu percepe modificarea coordonatelor maxime */
    getmaxyx(stdscr,y,x);
    if(y!=ymax || x!=xmax){
     erase();
     ymax=y; xmax=x;
     starty=dimy=ymax/3; startx=dimx=xmax/3; 
     midy=ymax/2; midx=xmax/2-5;
     ym=ymax-1; xm=xmax-1;
     border(0,0,0,0,0,0,0,0);
     mvhline(starty,startx,0,dimx);mvhline(starty+dimy,startx,0,dimx);
     mvvline(starty+1,startx,0,dimy-1);
     mvvline(starty+1,startx+dimx-1,0,dimy-1);
     mvprintw(midy,midx,"(%3d,%3d)",yc,xc);
     move(yc,xc);
     /* nu e necesar refresh, pt. ca am pus sus */
    }
    y=yc; x=xc;
    switch(c=getch()){
        case KEY_LEFT: if(xc>0)x=xc-1;break;
        case KEY_RIGHT: if(xc<xm)x=xc+1;break;
        case KEY_UP: if(yc>0)y=yc-1;break;
        case KEY_DOWN: if(yc<ym)y=yc+1;break;
        case 27: continua=0;break;
        case ' ':continua=0; 
    }
    if(x!=xc || y!=yc){
     yc=y; xc=x;
     mvprintw(midy,midx,"(%3d,%3d)",yc,xc);
     move(yc,xc);
     /* nu e necesar refresh, pt. ca am pus sus */
    }
  }while(continua);  
  endwin(); 
  return 0;
}
