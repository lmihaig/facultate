#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAXNRARG 10
#define MAXNRENV 10
int acvar(char *s1, char *s2){
  while(*s1 && *s2 && *s1==*s2 && *s1!='=' && *s2!='='){++s1; ++s2;}
  if((*s1=='=' && *s2=='=') ||
     (*s1=='=' && !*s2) ||
     (*s2=='=' && !*s1) ||
     (!*s1 && !*s2)
    )return 1;
  else return 0;
}
char buf[256], *a[MAXNRARG], *e[MAXNRENV]; int na, ne, i, j, k, s;
int main(){
ne=0; e[0]=NULL;
do{
  printf(">"); gets(buf); s=0; na=0;
  for(i=0;buf[i];++i)
    if(buf[i]==' ' && s==1){buf[i]='\0'; s=0;}
    else if(buf[i]!=' ' && s==0){a[na]=buf+i; ++na; s=1;}
  a[na]=NULL;
  if(a[0]==NULL)continue;
  else if(a[0][0]!='#')
         {if(!fork()){execve(a[0],a,e); return 1;} wait(NULL);}
  else if(!strcmp(a[0],"#set"))
   for(i=1;i<na;++i){
     for(j=0;j<ne;++j)if(acvar(a[i],e[j]))
      {e[j]=realloc(e[j],strlen(a[i])); strcpy(e[j],a[i]); break;}
     if(j==ne && ne<MAXNRENV-1)
      {e[ne]=(char *)malloc(strlen(a[i]));
       strcpy(e[j],a[i]); ++ne; e[ne]=NULL;}
   }
  else if(!strcmp(a[0],"#unset"))
   for(i=1;i<na;++i)for(j=0; j<ne; ++j){if(acvar(a[i],e[j]))
    {free(e[j]); for(k=j;k<ne;++k)e[k]=e[k+1]; --ne; break;}}
  else if(!strcmp(a[0],"#show"))
   for(i=0;i<ne;++i)printf("%s\n",e[i]);
  else if(!strcmp(a[0],"#exit"))break;
  else printf("Nu cunosc comanda: %s\n",a[0]);
}while(1);
return 0;
}
/* Necesita programul p29b.
   Utilizare:
   Lansam:
     p29a
   Apare un prompter ">"; in continuare dam comenzile urmatoare, iar pe
    ecran apare:
     >#show
     >#set a=1
     >#set bb=2 c=3
     >#show
     a=1
     bb=2
     c=3
     >#set bb=3
     >#show
     a=1
     bb=3
     c=3
     >p29b 1 2
     Program p29b:

     Argumente:
     p29b
     1
     2

     Environment:
     a=1
     bb=3
     c=3
     >#unset bb c
     >#show
     a=1
     >p29b x yyy
     Program p29b:

     Argumente:
     p29b
     x
     yyy

     Environment:
     a=1
     >#xx
     Nu cunosc comanda: #xx
     >#exit
     bash$
   ("bash$" e prompterul Linux).
*/