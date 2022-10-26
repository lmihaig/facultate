#include<iostream.h>

class rat{
 public:
  int s,j;
  rat(int, int);
  rat(int);         // necesar pentru conversii implicite de la int la rat
  operator double();// necesar pentru conversii implicite de la rat la double
  int operator<(rat);
};

rat::rat(int ps, int pj){s=ps; j=pj;}

rat::rat(int ps){

 s=ps; j=1;
}

rat::operator double(){return s/(double)j;}

int rat::operator<(rat r2){
  return (s*r2.j-r2.s*j)/(j*r2.j)<0;
}

void f(rat r){cout<<r.s<<"/"<<r.j<<endl;}

void g(double x){cout<<x<<endl;}

void main(){
  rat a(1,2),b(10,20);
  f(a); g(3.14);
  f(1); // nu merge daca nu definim constructorul "rat(int)"
  g(a); // nu merge daca nu definim operatorul de cast "double()"
  if(a<b)cout<<"a<b\n";    // se aplica "<" pt. "rat"
//  if(a<5)cout<<"a<b\n";
//      nu merge:
////    eroare de ambiguitate intre a aplica "rat(int)" si "<" pt. "rat"
////    si a aplica "double()" si "<" pt. "double"
  if(a<=5)cout<<"a<=b\n";  // se aplica "double()" si "<=" pt. "double"
  if(5<a)cout<<"5<a\n";    // se aplica "double()" si "<" pt. "double"
  if(5<=a)cout<<"5<=a\n";  // se aplica "double()" si "<=" pt. "double"
}

// constructorii de conversie si operatorii de cast sunt instrumente de
//   conversie pe care le definim in program explicit si care vor fi
//   folosite implicit;
// daca constructorul cu doi parametri ar fi avut al doilea parametru cu
//   valoare implicita (de exemplu "rat(int,int=1)"), puteam omite
//   constructorul "rat(int)"