// parametri cu valori implicite (1)

#include<iostream.h>

void f(int a, int b=2, int c=3){
  cout<<a<<" "<<b<<" "<<c<<endl;
}

void main(){
 f(10,20,30);
 f(10,20);
 f(10);
 // nu merge f();
}
