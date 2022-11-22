#include<iostream.h>
////////////////////////////////////////////////////
template <class t>
class lista{
 t *v;
 int n;
public:
 lista(int);
 t& operator[](int i) {return v[i];}
};
// definitiile metodelor in afara clasei necesita o sintaxa speciala
//  (atentie ca template<class t> trebuie pus inaintea fiecarei metode
//  definite in afara clasei, dar nu e necesar sa folosim acelasi nume t
//  la toate metodele):
template <class t>
lista<t>::lista(int pn){
  v=new t[pn]; n=pn;
}
////////////////////////////////////////////////////
class punct{
 int x,y;
public:
 punct(int px, int py){x=px; y=py;}
 punct(){} // fara el nu putem crea un vector de puncte
           //   in lista<punct>::lista; alternativ, constructorul
           //   anterior putea fi definit cu parametri impliciti
           //   de exemplu "punct(int px=0, int py=0)"
 friend ostream& operator<<(ostream &str, punct &p)
  {cout<<'('<<p.x<<','<<p.y<<')'; return str;}
};
////////////////////////////////////////////////////
void main(){
 lista<double> l1(4);
 lista<punct> l2(3);
 l1[0]=1.1; l1[1]=2.2; l1[2]=3.3; l1[3]=4.4;
 l2[0]=punct(10,20); l2[1]=punct(100,200); l2[2]=punct(1000,2000);
 int i;
 for(i=0;i<4;++i)cout<<l1[i]<<' '; cout<<endl;
 for(i=0;i<3;++i)cout<<l2[i]<<' '; cout<<endl;
}

/*
Idei:

- pentru fiecare utilizare a numelui clasei template (clasa generica) cu un
   alt tip efectiv intre <> pentru a defini un obiect, se creaza automat cate
   o clasa noua;
  de exemplu in programul de mai sus sunt 2 clase de tip lista: lista<int>
   (implementeaza liste de intregi) si lista<punct> (implementeaza liste de
   puncte);
  daca de exemplu am mai fi inserat in program:

    typedef lista<char> lc;

   si asta ar fi fost singurul loc unde ar fi aparut lista<char> sau lc,
   nu se crea o noua clasa, deoarece cu aceasta ocazie nu s-a creat nici un
   obiect;
  se pot folosi ca tipuri efective si constructii mai complexe, de exemplu
   lista<char *> (lista de pointeri la char, sau lista de stringuri);

- putem defini clase template cu mai multe tipuri generice, de exemplu:

   template<class t1, class t2, class t3> .... clasa ....

- compilatoarele mai noi de C++ au o biblioteca de template-uri de uz general
   numita STL (standard template library); acestea ofera algoritmi generici 
   pentru majoritatea operatiilor folosite in practica si de aceea se pot scrie
   programe folosind doar instantieri si metode ale acestor clase generice;
   de regula se prefera scrierea programelor folosind STL, deoarece codul 
   obtinut este mai scurt si mai portabil (cu cat conceptele folosite sunt mai
   abstracte si mai departate de nivelul hardware, codul este mai portabil);
   stilul de lucru si aspectul unui asemenea program pot fi insa mult diferite 
   de cele ale unui program C++ elementar (unde lucram mult cu tipurile simple 
   predefinite si operatorii uzuali), creand chiar impresia unui alt limbaj;
*/
