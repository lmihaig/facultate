#include<iostream.h>
#include<string.h>

class persoana{
 char nume[100];
public:
 void set(const char *pn){strcpy(nume,pn);}
 const char *getn(){return nume;}
};

class el:persoana{
 int venit;
public:
 void set(const char *pn, int pv){persoana::set(pn); venit=pv;}
 persoana::getn;
 int getv(){return venit;}
};

class ea:persoana{
 int consum;
public:
 void set(const char *pn, int pc){persoana::set(pn); consum=pc;}
 persoana::getn;
 int getc(){return consum;}
};

class familie:el,ea{
 int buget;
public:
 void set(el b, ea f){
  el::set(b.getn(),b.getv());
  ea::set(f.getn(),f.getc());
  buget=0;
 }
// el::getn;  // prezenta acestor metode produc erori de compilare,
// ea::getn;  //   care difera de la un compilator la altul
 int getb(){return buget;}
 void step(){buget=buget+getv()-getc();}
};

void main(){
 el b; b.set("Ion",10);
 ea f; f.set("Ana",15);
 familie ff; ff.set(b,f);
 ff.step(); ff.step(); ff.step();
 cout<<"Bugetul dupa 3 ani: "<<ff.getb()<<endl;
}
