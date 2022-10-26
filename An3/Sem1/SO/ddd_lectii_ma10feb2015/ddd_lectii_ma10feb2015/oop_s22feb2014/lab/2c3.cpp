// ilustrare constructori, destructori (3)

#include<iostream.h>

class c{
 public:
  int n;
  c(){cout<<"C0\n"; n=0;}
  c(int a){cout<<"C1\n"; n=a;}
  c(int a, char b){cout<<"C2: "<<endl; n=a+b;}
  ~c(){cout<<"d\n";}
};

void main(){
 cout<<"--------------------\n";
 c x, y(10), z(10,'a'); // putem scrie echivalent:  c x, y=10, z(10,'a');
 cout<<x.n<<", "<<y.n<<", "<<z.n<<endl;
}
