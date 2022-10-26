// clase (1)

#include <stdio.h>

class complex{
  public:
  double re; double im;
  void citeste(complex &a){
    scanf("%lf%lf",&a.re,&a.im);
  }
  void scrie(complex a){
    printf("%lf+i*%lf",a.re,a.im);
  }
};

void main()
{ complex x,y;
  printf("Dati primul numar complex (re, im): "); x.citeste(x);
  printf("Dati al doilea numar complex (re, im): "); y.citeste(y);
  printf("Am citit:\n"); x.scrie(x); printf("\n"); y.scrie(y); printf("\n");
}
