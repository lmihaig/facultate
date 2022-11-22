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
 cout<<"-- rat(int) --\n";
 s=ps; j=1;
}

rat::operator double(){
 cout<<"-- (double) --\n";
 return s/(double)j;
}

int rat::operator<(rat r2){
  cout<<"-- rat < rat --\n";
  return (s*r2.j-r2.s*j)/(j*r2.j)<0;
}

void f(rat r){cout<<r.s<<"/"<<r.j<<endl;}

void g(double x){cout<<x<<endl;}

void main(){
  rat a(1,2),b(10,20);
  f(a); g(3.14);
  f(1); // nu merge daca nu definim constructorul "rat(int)"
  g(a); // nu merge daca nu definim operatorul de cast "double()"
  if(a<b)cout<<"a<b\n";
//  if(a<5)cout<<"a<b\n"; // eroare de ambiguitate
  if(a<=5)cout<<"a<=b\n"; // se aplica "double()" si "<=" pt. "double"
  if(5<a)cout<<"5<a\n";   // se aplica "double()" si "<" pt. "double"
  if(5<=a)cout<<"5<=a\n"; // se aplica "double()" si "<=" pt. "double"
}
