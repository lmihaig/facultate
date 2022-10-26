#include<unistd.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(int na, char *a[]){
  DIR *pd; struct dirent *pde; struct stat s;
  char cale[256], specificator[256];
  char *arg[]={a[0],a[1],specificator,NULL}, *env[]={"numaratoare=0",NULL};
  int suma,status;
  if(na!=3){printf("Nr. gresit de argumente.\n"); return -1;}
  if(stat(a[2],&s)==-1)
    {printf("%s nu poate fi accesat.\n",a[2]); return -1;}
  if(!S_ISDIR(s.st_mode)){printf("%s nu e director.\n",a[2]); return -1;}
  if((pd=opendir(a[2]))==NULL)return 0;
  strcpy(cale,a[2]); strcat(cale,"/");
  for(pde=readdir(pd); pde; pde=readdir(pd)){
    strcpy(specificator,cale); strcat(specificator, pde->d_name);
    if(stat(specificator,&s)==-1)continue;
    if(S_ISDIR(s.st_mode))
     if(strcmp(pde->d_name,".") && strcmp(pde->d_name,".."))
      if(!fork())execve(a[0],arg,env);
  }
  rewinddir(pd);
  suma=0;
  for(pde=readdir(pd); pde; pde=readdir(pd)){
    strcpy(specificator,cale); strcat(specificator, pde->d_name);
    if(stat(specificator,&s)==-1)continue;
    if(S_ISREG(s.st_mode))if(!strcmp(a[1],pde->d_name)){suma=1; break;}
  }
  closedir(pd);
  while(wait(&status)>-1){suma+=WEXITSTATUS(status);}
  if(!getenv("numaratoare"))printf("Sunt %d aparitii.\n",suma);
  return suma;
}
/* Utilizare:
   Lansam:
     p26   p26.c   ..
   Pe ecran se afisaza numarul aparitiile lui "p26.c" in arborescenta cu
    originea in tatal directorului curent.
*/
