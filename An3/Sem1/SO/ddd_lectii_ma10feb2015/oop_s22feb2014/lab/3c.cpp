#include<iostream.h>
#include<stdlib.h>

class rat{
  int s,j;
 public:
  void set(int,int);
  int gets();
  int getj();
  rat(int);
  operator double();
  rat(int, int);
};

void rat::set(int ps, int pj){
 if(pj==0)exit(1);
 if(ps==0){s=0; j=1; return;}
 int a=ps>0?ps:-ps, b=pj>0?pj:-pj;
 while(a!=b) if(a>b) a-=b; else b-=a;
 s=ps/a; j=pj/a;
 if(j<0){s=-s; j=-j;}
}

int rat::gets(){return s;}

int rat::getj(){return j;}

rat::rat(int n){set(n,1);}

rat::operator double(){return s/(double)j;}

rat::rat(int ps, int pj){set(ps,pj);}

rat operator+(rat r1, rat r2){
  return rat(r1.gets()*r2.getj()+r2.gets()*r1.getj(),r1.getj()*r2.getj());
}

istream& operator>>(istream& s,rat &r){
  int a,b;
  s>>a>>b;
  r.set(a,b);
  return s;
}

ostream& operator<<(ostream& s,rat r){
  s<<r.gets();
  if(r.getj()!=1)s<<"/"<<r.getj();
  return s;
}

int main(){
 rat a(1,2),b(3,4);
 cout<<(a+b)<<endl;     // se aplica +(rat,rat) si << pentru rat
// cout<<(a+10)<<endl;  // eroare de ambiguitate
// cout<<(100+a)<<endl; // eroare de ambiguitate
 cout<<(100-a)<<endl;   // se aplica metoda double(), - si << pentru double
 return 0;
}
