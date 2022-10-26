#include<stdio.h>
FILE* f; char nume[100], c;
int main(){
 printf("Numele fisierului: "); scanf("%s",nume);
 if((f=fopen(nume,"rb"))==NULL){
  printf("Eroare la deschiderea fisierului %s\n",nume); return 1; 
 }
 for(fscanf(f,"%c",&c);!feof(f);fscanf(f,"%c",&c))printf("%c",c);
 fclose(f);
 return 0;
}
