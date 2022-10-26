// clase (3)

#include <stdio.h>

class complex{
  public:
  double re; double im;
  void citeste(){
    scanf("%lf%lf",&re,&im);
  }
  void scrie();
};

void complex::scrie(){
  printf("%lf+i*%lf",re,im);
}

void main()
{ complex x,y;
  printf("Dati primul numar complex (re, im): "); x.citeste();
  printf("Dati al doilea numar complex (re, im): "); y.citeste();
  printf("Am citit:\n"); x.scrie(); printf("\n"); y.scrie(); printf("\n");
}
