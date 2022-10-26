#include<iostream.h>
#include<string.h>

class persoana{
 char nume[100];
public:
 void set(const char *pn){strcpy(nume,pn);}
 const char *getn(){return nume;}
};

class ea:virtual persoana{
 int consum;
public:
 void set(const char *pn, int pc){persoana::set(pn); consum=pc;}
 persoana::getn;
 int getc(){return consum;}
};

class student:virtual persoana{
 int bursa;
public:
 void set(const char *pn, int pb){persoana::set(pn); bursa=pb;}
 persoana::getn;
 int getb(){return bursa;}
};

class studenta:ea,student{
 int venit;
public:
 void set(const char *pn, int pc, int pb){
  ea::set(pn,pc);
  student::set(pn,pb);
  venit=getb()-getc();
 }
   ea::getn;
// se poate folosi "student::getn" si doar pe unele
//   compilatoare "persoana::getn"
 int getv(){return venit;}
};

void main(){
 studenta s;
 s.set("Ana",15,10);
 cout<<"Studenta: "<<s.getn()<<", venit: "<<s.getv()<<endl;
}
