// cin, cout

#include <iostream.h>

class complex{
  double re; double im;
 public:
  void setre(double);
  void setim(double);
  double getre();
  double getim();
};

void complex::setre(double x){re=x;}
void complex::setim(double x){im=x;}
double complex::getre(){return re;}
double complex::getim(){return im;}

istream& operator>>(istream &s, complex &a){
  double x,y;
  s>>x>>y; a.setre(x); a.setim(y);
  return s;
}

ostream& operator<<(ostream &s, complex &a){
  s<<a.getre()<<"+i*"<<a.getim();
  return s;
}

complex operator+(complex a, complex b){
  complex c;
  c.setre(a.getre()+b.getre()); c.setim(a.getim()+b.getim());
  return c;
}
complex operator+(complex a, double b){
  complex c;
  c.setre(a.getre()+b); c.setim(a.getim());
  return c;
}
complex operator+(double a, complex b){
  complex c;
  c.setre(a+b.getre()); c.setim(b.getim());
  return c;
}

complex operator+(complex a){return a;}

complex operator-(complex  a){
  complex b;
  b.setre(-a.getre()); b.setim(-a.getim());
  return b;
}

void main()
{ complex x,y,z;
  cout<<"Dati primul numar complex (re, im): "; cin>>x;
  cout<<"Dati al doilea numar complex (re, im): "; cin>>y;
  double u,v;
  cout<<"Dati primul numar real: "; cin>>u;
  cout<<"Dati al doilea numar real: "; cin>>v;
  z=x+y; cout<<"Suma cc este: "<<z<<endl;
  z=x+u; cout<<"Suma cr este: "<<z<<endl;
  z=v+x; cout<<"Suma rc este: "<<z<<endl;
  z=+x;  cout<<"Numarul +x este: "<<z<<endl;
  z=-x;  cout<<"Numarul -x este: "<<z<<endl;
}

/* explicatie:

>>, << au supraincarcari implicite pentru cin, resp. cout, si toate tipurile predefinite;
pentru a functiona si cu tipuri (clase, structuri) defiunite de ut. trebuie supraincarcati
  explicit;

int a; double b;

cin>>a>>b;  <=>  (cin>>a)>>b;  
  (al doilea >> citeste din output-ul primului >>,
   de aceea el trebuie sa ret. acelasi stream din care a citit)

cout<<a<<b; <=>  (cout<<a)<<b;

pot supraincarca >>, << a.i. sa ret. void, dar atunci nu le mai pot inlantui:

class c1{.....} x;

class c2{.....} y;
 
ostream& operator<<(ostream& s, c1 p){... return s;}

void operator<<(ostream& s, c2 q){...}

cout<<a<<x<<b;

cout<<a<<y; cout <<b   (nu mai merge: cout<<a<<y<<b;)

*/
