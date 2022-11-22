#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include"fileinfo.i"
int listdir(const char *nf){
 DIR *pd; struct dirent *pde;
 char cale[256], specificator[256]; 
 if((pd=opendir(nf))==NULL)return -1;
 strcpy(cale, nf); strcat(cale,"/");
 while((pde=readdir(pd))!=NULL){
   strcpy(specificator, cale); strcat(specificator, pde->d_name);
   if(fileinfo(specificator)==-1)perror(specificator);
 }
 closedir(pd);
 return 0;
}
/* Fisier auxiliar pentru "p2" 
   Necesita fisierul "fileinfo.i" 
   Nu se foloseste singur */
