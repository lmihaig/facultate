// comentarii C++, eliminam struct, parametri prin referinta,
// supraincarcare functii, amestec declaratii cu instructiuni

#include <stdio.h>

struct complex{double re; double im;};

void citeste(complex &a){
  scanf("%lf%lf",&a.re,&a.im);
}

void scrie(complex a){
  printf("%lf+i*%lf",a.re,a.im);
}

complex aduna(complex a, complex b){
  complex c;
  c.re=a.re+b.re; c.im=a.im+b.im;
  return c;
}
complex aduna(complex a, double b){
  complex c;
  c.re=a.re+b; c.im=a.im;
  return c;
}
complex aduna(double a, complex b){
  complex c;
  c.re=a+b.re; c.im=b.im;
  return c;
}

void main()
{ complex x,y,z;
  printf("Dati primul numar complex (re, im): "); citeste(x);
  printf("Dati al doilea numar complex (re, im): "); citeste(y);
  double u,v;
  printf("Dati primul numar real: "); scanf("%lf",&u);
  printf("Dati al doilea numar real: "); scanf("%lf",&v);
  z=aduna(x,y); printf("Suma cc este: "); scrie(z); printf("\n");
  z=aduna(x,u); printf("Suma cr este: "); scrie(z); printf("\n");
  z=aduna(v,x); printf("Suma rc este: "); scrie(z); printf("\n");
}
