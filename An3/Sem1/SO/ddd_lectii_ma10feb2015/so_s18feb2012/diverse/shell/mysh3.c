#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>

char ldc[256], c0[256], c1[256], c2[256], *a[256];

int main(){
  while(1){
    printf(">>");
    gets(ldc);
    c0[0]=c1[0]=c2[0]=0;
    sscanf(ldc,"%s%s%s",c0,c1,c2);
    if(!strcmp(c0,"exit")){
      return 0;
    }else if(!strcmp(c1,"|")){                              /**********/
      int d[2];                                             /**********/
      pipe(d);                                              /**********/
      if(!fork()){                                          /**********/
        close(1); dup(d[1]); close(d[0]); close(d[1]);      /**********/
        a[0]=c0; a[1]=NULL;                                 /**********/
        execv(c0,a);                                        /**********/
        return 1;                                           /**********/
      }else if(!fork()){                                    /**********/
        close(0); dup(d[0]); close(d[0]); close(d[1]);      /**********/
        a[0]=c2; a[1]=NULL;                                 /**********/
        execv(c2,a);                                        /**********/
        return 1;                                           /**********/
      }else{                                                /**********/
        close(d[0]); close(d[1]); while(wait(NULL)!=-1);    /**********/
      }                                                     /**********/
    }else if(fork()){
            wait(NULL);
          }else{
            if(!strcmp(c1,">")){
              int d;
              if((d=open(c2,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR))==-1) return 1;
              close(1); dup(d); close(d);
            }
            a[0]=c0; a[1]=NULL;
            execv(c0,a);
            return 1;
          }
  }
  return 0;
}
