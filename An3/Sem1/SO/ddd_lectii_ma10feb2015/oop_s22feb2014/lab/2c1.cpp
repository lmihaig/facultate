// ilustrare constructori, destructori (1)

#include<iostream.h>

class c{
 public:
  c(){cout<<"C: "<<this<<endl;}
  ~c(){cout<<"d: "<<this<<endl;}
};

void f(){c y;}

void main(){
 cout<<"--------------------\n";
 c x;
 c *p;
 p=new c;
 delete p;
 f();
}
