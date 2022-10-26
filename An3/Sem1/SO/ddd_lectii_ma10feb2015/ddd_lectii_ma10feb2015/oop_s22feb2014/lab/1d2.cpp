// clase (2)

#include <stdio.h>

class complex{
  public:
  double re; double im;
  void citeste(){
    scanf("%lf%lf",&re,&im);
  }
  void scrie(){
    printf("%lf+i*%lf",re,im);
  }
};

void main()
{ complex x,y;
  printf("Dati primul numar complex (re, im): "); x.citeste();
  printf("Dati al doilea numar complex (re, im): "); y.citeste();
  printf("Am citit:\n"); x.scrie(); printf("\n"); y.scrie(); printf("\n");
}

/* cod echivalent:

class complex{
  public:
  double re; double im;
  void citeste(complex *this){
    scanf("%lf%lf",&this->re,&this->im);
  }
  void scrie(complex *this){
    printf("%lf+i*%lf",this->re,this->im);
  }
};

void main()
{ complex x,y;
  printf("Dati primul numar complex (re, im): "); x.citeste(&x);
  printf("Dati al doilea numar complex (re, im): "); y.citeste(&y);
  printf("Am citit:\n"); x.scrie(&x); printf("\n"); y.scrie(&y); printf("\n");
}

*/
