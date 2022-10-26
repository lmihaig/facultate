// parametri cu valori implicite (2)

#include<iostream.h>

void f(int x, double y){cout<<"f int double\n";}

void f(double x, int y){cout<<"f double int\n";}

void g(int x){cout<<"g int\n";}

void g(int x, int y=2){cout<<"g int int\n";}

void main(){
 f(10,3.14);  // aplic f(int,double)
 f(3.14,10);  // aplic f(double,int)
// f(10,10);    // eroare: ambiguitate

// g(10);       // eroare: ambiguitate intre g(10) si g(10,2)
}
