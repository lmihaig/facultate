#include<iostream.h>
#include<string.h>

class p{  // persoana
 char *n; // nume
public:
 p(char *);
 ~p();
 //virtual ~p();
 void show();
 //virtual void show();
};
p::p(char *pn){n=new char[strlen(pn)+1]; strcpy(n,pn); cout<<"c-p\n";}
p::~p(){delete n; cout<<"d-p\n";}
void p::show(){cout<<n<<endl;}

class a:public p{  // angajat
 char *m; // meserie
public:
 a(char *, char *);
 ~a();
 void show();
 void test();
};
a::a(char *pn, char *pm):p(pn)
  {m=new char[strlen(pm)+1]; strcpy(m,pm); cout<<"c-a\n";}
a::~a(){delete m; cout<<"d-a\n";}
void a::show(){p::show(); cout<<m<<endl;}
void a::test(){}

void main(){
 p *v[2]; int i;
 cout<<"-----\n\n";
 v[0]=new p("Ion"); cout<<endl; v[1]=new a("Mihai","zidar"); cout<<endl;
 for(i=0;i<2;++i){v[i]->show(); cout<<endl;}
 //v[1]->test(); // eroare (si cu, si fara virtual):
		 //   'test' is not a member of 'p'
 v[1]->p::show();
 cout<<endl;
 for(i=0;i<2;++i){delete v[i]; cout<<endl;}
}
