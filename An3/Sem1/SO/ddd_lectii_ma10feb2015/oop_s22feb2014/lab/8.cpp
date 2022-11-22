#include<iostream.h>

class persoana{
 virtual char *salut()=0; // lipseste implementarea
public:
 void saluta(){cout<<salut()<<'!'<<endl;}
};

class roman:public persoana{
 virtual char *salut(){return "Salut";}
};

class englez:public persoana{
 virtual char *salut(){return "Hello";}
};

void main(){
 //persoana p; // eroare: Cannot create instance of abstract class 'persoana'
 roman r; englez e;
 r.saluta(); e.saluta();
}
