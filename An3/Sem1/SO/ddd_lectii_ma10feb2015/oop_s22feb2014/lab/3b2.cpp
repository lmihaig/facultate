#include<iostream.h>
#include<stdlib.h>

class rat{
  int s,j;
  void norm();  
 public:
  rat(int);             /* noutate */
  operator double();    /* noutate */
  rat(int, int);
  rat operator+(rat);   /* noutate - am doar un +  */
 friend istream& operator>>(istream&,rat&);
 friend ostream& operator<<(ostream&,rat);
};

rat::rat(int n){        /* noutate */
 s=n; j=1;              /* noutate */
 norm();                /* noutate */
}                       /* noutate */

rat::operator double(){ /* noutate */
 return s/(double)j;    /* noutate */
}                       /* noutate */

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
 // cout<<(a+10)<<endl;  // eroare de ambiguitate
 cout<<(100+a)<<endl; // se aplica metoda double(), + si << pentru double
 cout<<(100-a)<<endl; // se aplica metoda double(), - si << pentru double
 return 0;
}

// concluzie: prezenta instrumentelor de conversie implicita ne permite
//   sa reducem numarul de supraincarcari;
// nota: alegerea implicita a conversiilor si semnalarea de ambiguitati
//   poate diferi de la un compilator la altul
