// ilustrare constructori, destructori (4)

#include<iostream.h>

class c{
 public:
  int n;
  c(int a=0, char b=0){cout<<"C0: "<<endl; n=a+b;}
  ~c(){cout<<"d\n";}
};

void main(){
 cout<<"--------------------\n";
 c x, y(10), z(10,'a'); // putem scrie echivalent:  c x, y=10, z(10,'a');
 cout<<x.n<<", "<<y.n<<", "<<z.n<<endl;
}

/* deci folosind parametrii cu valori implicite putem reduce numarul
 constructorilor */
