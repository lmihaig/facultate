#include<iostream.h>
struct nod{int inf; nod *leg;};
class stiva{
 nod *v;
public:
 stiva();
 ~stiva();
 stiva& operator<<(int);
 stiva& operator>>(int&);
 int vida();
};
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
 int v[]=//{2,1,-1,2,3,-3,-2,-2}; // corect
	 {2,1,-2}; // gresit
	 //{2,1,-1,2,3,-2,-2}; // gresit
	 //{3,3,-3,2,3,-3,1,2,-2,-1,3,1,-1,-3,-2,1,1,-1,-1,-3}; //corect
 int n=sizeof(v)/sizeof(int),i;
 for(i=0;i<n;++i)
  if(v[i]>0)s<<v[i]; //nr. pozitiv = paranteza deschisa
  else{if(s.vida())break;
       int k;  s>>k; if(k!=-v[i])break;
      }
 if(s.vida() && i==n)cout<<"Sir corect\n"; else cout<<"Sir gresit\n";
}
