#include<iostream.h>
#define MAX 100

class matrice{
 int l,c,v[MAX];
public:
 void set(int,int);
 int getl();
 int getc();
 int* operator[](int);
};

void matrice::set(int pl, int pc){
 if(pl<0 || pc<0 || pl*pc>MAX)l=c=0;
 else{l=pl; c=pc;}
}
int matrice::getl(){return l;}
int matrice::getc(){return c;}
int* matrice::operator[](int i){return &v[i*c];}

void main(){
 matrice a; int i,j;
 a.set(2,3);
 cout<<"Dati o matrice 2x3 de intregi:\n";
 for(i=0;i<2;++i)for(j=0;j<3;++j)cin>>a[i][j];
 cout<<"Matricea este:\n";
 for(i=0;i<2;++i){
  for(j=0;j<3;++j)cout<<a[i][j]<<' ';
  cout<<endl;
 }
}
