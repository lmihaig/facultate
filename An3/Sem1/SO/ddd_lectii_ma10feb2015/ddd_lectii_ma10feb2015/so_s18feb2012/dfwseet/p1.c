#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
int main(){
 int d; char x;
 d=open("f",O_RDWR|O_APPEND);
 printf("%ld ",lseek(d,0l,SEEK_CUR));
 write(d,"x",1);
 printf("%ld ",lseek(d,0l,SEEK_CUR));
 lseek(d,0l,SEEK_SET);
 read(d,&x,1);
 printf("%ld ",lseek(d,0l,SEEK_CUR));
 write(d,"y",1);
 printf("%ld ",lseek(d,0l,SEEK_CUR));
 read(d,&x,1);
 printf("%ld\n",lseek(d,0l,SEEK_CUR));
return 0;
}
/* Utilizare:
   Cream un fisier "f" care contine 6 caractere.
   Lansam:
     p1
   Se va afisa:
     0 7 1 8 8
*/
