#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<pwd.h>
#include<sys/types.h>
#include<time.h>
int fileinfo(const char *nf){
  struct stat s; struct passwd *pp; struct tm *pt; 
  if(stat(nf,&s)==-1)return -1;
  if((pp=getpwuid(s.st_uid))==NULL)return -1;
  switch(s.st_mode & S_IFMT){
    case S_IFREG: printf("-"); break;
    case S_IFDIR: printf("d"); break;
    otherwise: printf("o");  
  }
  if(s.st_mode & S_IRUSR)printf("r");else printf("-");
  if(s.st_mode & S_IWUSR)printf("w");else printf("-");
  if(s.st_mode & S_IXUSR)printf("x");else printf("-");
  if(s.st_mode & S_IRGRP)printf("r");else printf("-");
  if(s.st_mode & S_IWGRP)printf("w");else printf("-");
  if(s.st_mode & S_IXGRP)printf("x");else printf("-");
  if(s.st_mode & S_IROTH)printf("r");else printf("-");
  if(s.st_mode & S_IWOTH)printf("w");else printf("-");
  if(s.st_mode & S_IXOTH)printf("x");else printf("-");
  printf("     %-8s",pp->pw_name);
  if((s.st_mode & S_IFMT) == S_IFREG)printf("%12ld",s.st_size); else
  if((s.st_mode & S_IFMT) == S_IFDIR)printf("       <DIR>");
  pt=gmtime(&s.st_mtime); 
  printf("     %02d/%02d/%4d",pt->tm_mday,pt->tm_mon+1,pt->tm_year+1900);
  printf(" %s\n",nf);
  return 0;
}
/* Fisier auxiliar pentru "listdir.i", "p1" si "p2"
   Nu se foloseste singur */
