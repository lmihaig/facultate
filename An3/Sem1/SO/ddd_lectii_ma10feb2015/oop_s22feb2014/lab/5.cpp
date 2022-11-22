#include<iostream.h>

class stack{
 struct nod{void *inf; nod *leg;} *v;
public:
 int empty(){return v==NULL;}
 int push(void *pinf){
  nod *n=new nod; if(n==NULL)return 0;
  n->inf=pinf; n->leg=v; v=n;
  return 1;
 }
 void * pop(int &ok){
   if(empty()){ok=0; return NULL;}
   void *r=v->inf;
   nod *n=v; v=v->leg; delete n;
   ok=1; return r;
 }
 stack(){v=NULL;}
 ~stack(){for(int n=1; n; pop(n));}
};

class unit{
 int x,y;
public:
 unit(int px,int py){x=px; y=py;}
 void get(int &px, int &py){px=x; py=y;}
 void show(){cout<<x<<','<<y<<endl;}
 void move(int dx, int dy){x+=dx; y+=dy;}
};

class memunit:unit, stack{
public:
 unit::get;
 unit::show;
 memunit(int px, int py):unit(px,py){}
 int move(int dx, int dy){
  int *d=new int[2]; d[0]=dx; d[1]=dy;
  if(push(d)){unit::move(dx,dy); return 1;}
        else {delete []d; return 0;}
 }
 int retreat(){
  int *d,n;
  d=(int*)pop(n);
  if(n){unit::move(-d[0],-d[1]); delete []d; return 1;}
   else return 0;
 }
};

void main(){
 cout<<"------------------\n";
 memunit u(10,10);
 int v[][2]={{1,-1},{0,1},{1,0}}, n=sizeof(v)/(2*sizeof(int));
 u.show();
 for(int i=0;i<n;++i) if(u.move(v[i][0],v[i][1])) u.show();
 u.show();
 while(u.retreat()) u.show();
}
