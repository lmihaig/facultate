#include<iostream.h>
    // noutate:
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
    // noutate:
    stiva(int,int *);
    stiva(int,...);
    friend ostream& operator<<(ostream&,stiva&);
      //err la executie daca stiva e fara &
};
    // noutate:
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
stiva::~stiva(){int n; while(!vida())operator>>(n);}
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

void main(){
 stiva s;
 int v[]=//{2,1,-1,2,3,-3,-2,-2};
	   {2,1,-2};
	   //{2,1,-1,2,3,-2,-2};
	   //{3,3,-3,2,3,-3,1,2,-2,-1,3,1,-1,-3,-2,1,1,-1,-1,-3};
 int n=sizeof(v)/sizeof(int),i;
    // noutate:
    stiva s1(3,1,2,3);
    cout<<s1<<endl;
    cout<<s1<<endl;
    stiva s2(n,v);
    cout<<s2<<endl;
}
