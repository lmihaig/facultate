#include<iostream.h>
#include<stdarg.h>
struct nod{int inf; nod *leg;};
class stiva{
 nod *v;
public:
 stiva();
 ~stiva();
 stiva& operator<<(int);
 stiva& operator>>(int&);
 int vida();
 stiva(int,int *);
 stiva(int,...);
 friend ostream& operator<<(ostream&,stiva&);
};
stiva::stiva(int n, int *pv){
 v=NULL; for(int i=0;i<n;++i)operator<<(pv[i]);
}
stiva::stiva(int n,...){
 va_list l; int i;
 va_start(l,n);
 v=NULL; for(i=0;i<n;++i)operator<<(va_arg(l,int));
 va_end(l);
}
ostream& operator<<(ostream&s,stiva &x){
 stiva aux; int n;
 while(!x.vida()){x>>n; aux<<n; s<<n<<' ';}
 while(!aux.vida()){aux>>n; x<<n;}
 return s;
}
stiva::stiva(){v=NULL;}
stiva::~stiva(){int n;while(!vida())operator>>(n);}
stiva& stiva::operator<<(int n){
 nod *p;
 if((p=new nod)!=NULL){p->inf=n; p->leg=v; v=p;}
 return *this;
}
stiva& stiva::operator>>(int &n){
 nod *p;
 if(!vida()){n=v->inf; p=v; v=v->leg; delete p;}
 return *this;
}
int stiva::vida(){return v==NULL;}

// noutate:
class stivam:stiva{
 int n,k;
public:
 stivam(int);
 stivam(int,int,int *);
 stivam(int,int,...);
 int nr();
 stivam& operator<<(int);
 stivam& operator>>(int&);
 stiva::vida;
 friend ostream& operator<<(ostream&,stivam&);
};
stivam::stivam(int pn){n=pn; k=0;} // se apeleaza automat: stiva()
stivam::stivam(int pn,int pk, int *pv):stiva(pk,pv){n=pn>=pk?pn:pk; k=pk;}
stivam::stivam(int pn,int pk,...){ // se apeleaza automat: stiva()
 n=pn>=pk?pn:pk; k=0;
 va_list l; int i;
 va_start(l,pk);
 for(i=0;i<pk;++i)operator<<(va_arg(l,int));
 va_end(l);
}
// nu este necesar sa adaugam clasei "stivam" un destructor definit de
//   utilizator; notam ca destructorul implicit adaugat de compilator
//   acestei clase apeleaza automat "~stiva()" (destructor definit de
//   utilizator)
int stivam::nr(){return k;}
stivam& stivam::operator<<(int x)
  {if(k<n){stiva::operator<<(x);++k;}return *this;}
stivam& stivam::operator>>(int& x)
  {if(k>0){stiva::operator>>(x);--k;}return *this;}
ostream& operator<<(ostream&s,stivam&x){s<<*(stiva*)&x; return s;}
       //daca ziceam doar: (stiva)x dadea Null pointer assignement

void main(){
 int v[]={2,1,-2};
 int n=sizeof(v)/sizeof(int),x;
// noutate:
 stivam s(5,n,v),s1(10),s2(5,3,1,2,3);
 cout<<"Stiva: "<<s<<", incarcare: "<<s.nr()<<endl;
 s<<10<<20<<30<<40<<50;
 cout<<"Stiva: "<<s<<", incarcare: "<<s.nr()<<endl;
 s>>x>>x>>x;
 cout<<"Stiva: "<<s<<", incarcare: "<<s.nr()<<endl;
 cout<<"Stiva: "<<s1<<", incarcare: "<<s1.nr()<<endl;
 cout<<"Stiva: "<<s2<<", incarcare: "<<s2.nr()<<endl;
}