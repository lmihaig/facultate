#include<iostream.h>
#include<string.h>

class persoana{
 char nume[100];
 char* getn();
 char* getc();
 // virtual char* getc();
public:
 void set(const char *);
 void show();
};
char* persoana::getn(){return nume;}
char* persoana::getc(){return "Persoana";}
void persoana::set(const char *pn){strcpy(nume,pn);}
void persoana::show(){cout<<getc()<<": "<<getn()<<endl;}


class student:public persoana{
 char* getc();
 // virtual char* getc(); // aici "virtual" se poate omite
};
char* student::getc(){return "Studentul";}

void main(){
 persoana p; p.set("Ion");
 student s;  s.set("Nicu");
 p.show(); s.show();
}
