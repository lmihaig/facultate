// public, privat (1)

#include <stdio.h>

class complex{
  double re; double im;  // implicit private la clase si publice la structuri
  public:
  void citeste();
  friend void scrie(complex);
};

void complex::citeste(){
  scanf("%lf%lf",&re,&im);
}

void scrie(complex a){
  printf("%lf+i*%lf",a.re,a.im);
}

/* gresit (aici nu se pot accesa membrii privati ai clasei complex):
complex operator-(complex a){
  complex b;
  b.re=-a.re; b.im=-a.im;
  return b;
}
*/

void main()
{ complex x;
  printf("Dati un numar complex (re, im): "); x.citeste();
  printf("Am citit: "); scrie(x); printf("\n");
  /* gresit (aici nu se pot accesa membrii privati ai clasei complex):
   x.re=100;
  */
}
