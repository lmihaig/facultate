#include<iostream.h>
#include<stdlib.h>

class rat{
  int s,j;
  void norm();  
 public:
  rat(int, int);
  rat operator+(rat);
  rat operator+(int);
 friend rat operator+(int,rat);
 friend istream& operator>>(istream&,rat&);
 friend ostream& operator<<(ostream&,rat);
};

void rat::norm(){
 if(j==0)exit(1);
 if(s==0) {j=1; return;}
 int a=s>0?s:-s, b=j>0?j:-j;
 while(a!=b) if(a>b) a-=b; else b-=a;
 s/=a; j/=a;
 if(j<0){s=-s; j=-j;}
}

rat::rat(int ps, int pj){
 s=ps; j=pj;
 norm();
}

rat rat::operator+(rat r2){
  return rat(s*r2.j+r2.s*j,j*r2.j);
}

rat rat::operator+(int n){
  return rat(s+n*j,j);
}

rat operator+(int n,rat r2){
  return rat(n*r2.j+r2.s,r2.j);
}

istream& operator>>(istream& s,rat &r){
  s>>r.s>>r.j;
  r.norm();
  return s;
}

ostream& operator<<(ostream& s,rat r){
  s<<r.s;
  if(r.j!=1)s<<"/"<<r.j;
  return s;
}

int main(){
 rat a(1,2),b(3,4);
 cout<<(a+b)<<endl;   // se aplica metoda +(rat) si << pentru rat
 cout<<(a+10)<<endl;  // se aplica metoda +(int) si << pentru rat
 cout<<(100+a)<<endl; // se aplica functia +(int,rat) si << pentru rat
 // nu merge: cout<<(100-a)<<endl;
 return 0;
}
