// clase (4)

#include <stdio.h>

class complex{
  public:
  double re; double im;
  void citeste();
  void scrie();
  complex operator+(complex);  // complex+complex
  complex operator+(double);   // complex+double
  complex operator+();         // + unar
};

void complex::citeste(){
  scanf("%lf%lf",&re,&im);
}

void complex::scrie(){
  printf("%lf+i*%lf",re,im);
}

complex complex::operator+(complex b){
  complex c;
  c.re=re+b.re; c.im=im+b.im;
  return c;
}
complex complex::operator+(double b){
  complex c;
  c.re=re+b; c.im=im;
  return c;
}
complex operator+(double a, complex b){  // functie independenta
  complex c;
  c.re=a+b.re; c.im=b.im;
  return c;
}

complex complex::operator+(){return *this;}

complex operator-(complex a){  // functie independenta (putea fi si metoda)
  complex b;
  b.re=-a.re; b.im=-a.im;
  return b;
}

void main()
{ complex x,y,z;
  printf("Dati primul numar complex (re, im): "); x.citeste();
  printf("Dati al doilea numar complex (re, im): "); y.citeste();
  double u,v;
  printf("Dati primul numar real: "); scanf("%lf",&u);
  printf("Dati al doilea numar real: "); scanf("%lf",&v);
  z=x+y; printf("Suma cc este: "); z.scrie(); printf("\n");
  z=x+u; printf("Suma cr este: "); z.scrie(); printf("\n");
  z=v+x; printf("Suma rc este: "); z.scrie(); printf("\n");
  z=+x;  printf("Numarul +x este: "); z.scrie(); printf("\n");
  z=-x;  printf("Numarul -x este: "); z.scrie(); printf("\n");
}

/*
 In loc de z=x+y; pot scrie z=x.operator+(y);
 In loc de z=v+x; pot scrie z=operator+(v,x);
*/
