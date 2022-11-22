// ilustrare constructori, destructori (2)

#include<iostream.h>

class c{
 public:
  c(){cout<<"C: "<<this<<endl;}
  ~c(){cout<<"d: "<<this<<endl;}
};

void main(){
 cout<<"--------------------\n";
 c x;
 c *p;
 p=new c[3];
 delete []p;
 p=new c[3];
 delete p;
}

/* la "p=new c[3];" elementelor vectorului li se aplica un constructor
  fara parametri; deci, fie nu trebuie sa declaram nici un cosntructor nou
  (si atunci se foloseste cel predefit, care nu are parametri), fie (daca
  am declarat constructori utilizator) trebuie sa declaram cel putin un
  constructor fara parametrii sau cu toti parametrii avand valori implicite
  (deoarece in acest caz constructorul predefinit nu mai exista separat);
   la unele compilatoare, programul generat produce erori la exectie din
  cauza secventei " p=new c[3]; delete p;"
*/
