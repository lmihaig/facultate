/* varianta C */

#include <stdio.h>

struct complex{double re; double im;};

void citeste(struct complex *a){
  scanf("%lf%lf",&a->re,&a->im);
}

void scrie(struct complex a){
  printf("%lf+i*%lf",a.re,a.im);
}

struct complex aduna_cc(struct complex a, struct complex b){
  struct complex c;
  c.re=a.re+b.re; c.im=a.im+b.im;
  return c;
}

struct complex aduna_cr(struct complex a, double b){
  struct complex c;
  c.re=a.re+b; c.im=a.im;
  return c;
}

struct complex aduna_rc(double a, struct complex b){
  struct complex c;
  c.re=a+b.re; c.im=b.im;
  return c;
}

int main()
{ struct complex x,y,z; double u,v;
  printf("Dati primul numar complex (re, im): "); citeste(&x);
  printf("Dati al doilea numar complex (re, im): "); citeste(&y);
  printf("Dati primul numar real: "); scanf("%lf",&u);
  printf("Dati al doilea numar real: "); scanf("%lf",&v);
  z=aduna_cc(x,y); printf("Suma cc este: "); scrie(z); printf("\n");
  z=aduna_cr(x,u); printf("Suma cr este: "); scrie(z); printf("\n");
  z=aduna_rc(v,x); printf("Suma rc este: "); scrie(z); printf("\n");
}
