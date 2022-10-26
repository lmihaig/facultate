#include<stdio.h>
FILE* f; char nume[100], c;
int main(){
 printf("Numele fisierului: "); scanf("%s",nume);
 if((f=fopen(nume,"rb"))==NULL){
  printf("Eroare la deschiderea fisierului %s\n",nume); return 1; 
 }
 while(fscanf(f,"%c",&c)>0) printf("%c",c);
 fclose(f);
 return 0;
}