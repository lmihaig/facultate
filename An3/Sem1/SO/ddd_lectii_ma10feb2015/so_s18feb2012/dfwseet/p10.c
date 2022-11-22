#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

void cauta(const char *nf, const char *specd){
  DIR *pd; struct dirent *pde; struct stat s;
  char cale[256], specificator[256];
  if((pd=opendir(specd))==NULL)return;
  strcpy(cale,specd); strcat(cale,"/");
  for(pde=readdir(pd); pde; pde=readdir(pd)){
    strcpy(specificator,cale); strcat(specificator, pde->d_name);
    if(stat(specificator,&s)==-1)continue;
    if(S_ISDIR(s.st_mode))
     if(strcmp(pde->d_name,".") && strcmp(pde->d_name,".."))
      if(!fork()){cauta(nf,specificator); exit(0);}
  }
  rewinddir(pd);
  for(pde=readdir(pd); pde; pde=readdir(pd)){
    strcpy(specificator,cale); strcat(specificator, pde->d_name);
    if(stat(specificator,&s)==-1)continue;
    if(S_ISREG(s.st_mode))
      if(!strcmp(nf,pde->d_name))printf("%s\n",specificator);
  }
  closedir(pd);
}

int main(int na, char *a[]){struct stat s;
  if(na!=3)return 1;
  if(stat(a[2],&s)==-1){perror(a[2]); return 1;}
  if(!S_ISDIR(s.st_mode)){printf("%s nu e director.\n",a[2]); return 1;}
  cauta(a[1],a[2]);
  return 0;
}
/* Utilizare:
   Setam:
     stty -tostop
   Lansam:
     p10   p10.c   ..   &
   Pe ecran se afisaza toate aparitiile lui "p10.c" in arborescenta cu
    originea in tatal directorului curent (cu cale cu tot).
*/
