// public, privat - principiul incapsularii datelor

#include <stdio.h>

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

void citeste(complex &a){
  double x,y;
  scanf("%lf",&x); a.setre(x);
  scanf("%lf",&y); a.setim(y);
}

void scrie(complex &a){
  printf("%lf+i*%lf",a.getre(),a.getim());
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

complex operator-(complex  b){
  complex b;
  b.setre(-a.getre()); b.setim(-a.getim());
  return b;
}

void main()
{ complex x,y,z;
  printf("Dati primul numar complex (re, im): "); citeste(x);
  printf("Dati al doilea numar complex (re, im): "); citeste(y);
  double u,v;
  printf("Dati primul numar real: "); scanf("%lf",&u);
  printf("Dati al doilea numar real: "); scanf("%lf",&v);
  z=x+y; printf("Suma cc este: "); scrie(z); printf("\n");
  z=x+u; printf("Suma cr este: "); scrie(z); printf("\n");
  z=v+x; printf("Suma rc este: "); scrie(z); printf("\n");
  z=+x;  printf("Numarul +x este: "); scrie(z); printf("\n");
  z=-x;  printf("Numarul -x este: "); scrie(z); printf("\n");
}
