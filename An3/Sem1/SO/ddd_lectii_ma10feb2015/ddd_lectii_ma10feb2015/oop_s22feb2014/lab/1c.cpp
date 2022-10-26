// supraincarcare operatori

#include <stdio.h>

struct complex{double re; double im;};

void citeste(complex &a){
  scanf("%lf%lf",&a.re,&a.im);
}

void scrie(complex a){
  printf("%lf+i*%lf",a.re,a.im);
}

complex operator+(complex a, complex b){
  complex c;
  c.re=a.re+b.re; c.im=a.im+b.im;
  return c;
}
complex operator+(complex a, double b){
  complex c;
  c.re=a.re+b; c.im=a.im;
  return c;
}
complex operator+(double a, complex b){
  complex c;
  c.re=a+b.re; c.im=b.im;
  return c;
}

complex operator+(complex a){return a;}

complex operator-(complex a){
  complex b;
  b.re=-a.re; b.im=-a.im;
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

/*
 In loc de z=x+y; pot scrie z=operator+(x,y);
*/
