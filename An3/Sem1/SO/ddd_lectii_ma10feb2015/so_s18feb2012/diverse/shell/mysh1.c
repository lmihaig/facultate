#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>

char ldc[256], c0[256], *a[256];

int main(){
  while(1){
    printf(">>");
    gets(ldc);
    c0[0]=0;
    sscanf(ldc,"%s",c0);
    if(!strcmp(c0,"exit")){
      return 0;
    }else if(fork()){
            wait(NULL);
          }else{
            a[0]=c0; a[1]=NULL;
            execv(c0,a);
            return 1;
          }
  }
  return 0;
}
