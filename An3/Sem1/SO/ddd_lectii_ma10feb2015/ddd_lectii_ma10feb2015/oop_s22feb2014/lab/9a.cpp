#include<iostream.h>
#include<string.h>
////////////////////////////////////////////////////
template<class t>
t max(t x, t y){return x<y?y:x;}

template<class t>
void swap(t &x, t &y){
 t z;
 z=x; x=y; y=z;
}
////////////////////////////////////////////////////
class sir{
 char *s;
public:
 sir(char *ps=NULL){
  if(!ps){s=NULL; return;}
  s=new char[strlen(ps)+1]; strcpy(s,ps);
 }
 sir operator=(sir &x){
  delete s;
  if(x.s){s=new char[strlen(x.s)+1]; strcpy(s,x.s);}
  else{s=NULL;}
  return *this;
 }
 int operator<(sir &x){
  if(!x.s)return 0;
  return strcmp(s,x.s)<0;
 }
 friend ostream& operator<<(ostream &str, sir &x)
  {if(x.s)str<<x.s; return str;}
};
////////////////////////////////////////////////////
void main(){
 int x=10, y=20, z;
 double a=10.1, b=20.1, c;
 sir u("abc"), v("defg"), w("hi");
 cout<<"=============================\n";
 z=max(x,y); cout<<z<<endl;
 c=max(a,b); cout<<c<<endl;
 w=max(u,v); cout<<w<<endl;
 cout<<"-----------------------------\n";
 swap(x,y); cout<<x<<' '<<y<<endl;
 swap(a,b); cout<<a<<' '<<b<<endl;
 swap(u,v); cout<<u<<' '<<v<<endl;
}

/*
Idei:

- template (sabloanele) au fost introduse in C++ mai tarziu, in 1990;
  acum fac parte din standardul ANSI C++;

- putem defini functii template (functii sablon, functii generice) cu mai
   multe tipuri generice, de exemplu:

   template<class t1, class t2, class t3> .... functie ....

- pentru fiecare apel al unei functii template cu parametri de alt tip se
   creaza cate o noua instantiere (supraincarcare) a functiei respective;
  in programul de mai sus exista 3 functii max (una cu parametri int, alta
   cu parametri double si alta cu parametri sir) si 3 functii swap (cu
   parametri int&, double&, respectiv sir&);

- o functie template implementeaza un algoritm generic, care poate fi aplicat
   oricaror tipuri de date care poseda in interfata lor operatiile folosite
   in algoritm;
  de exemplu functia max se poate aplica oricaror tipuri de date pentru care
   este definit un operator <;

- daca supraincarcam explicit o functie template, atunci pentru tipurile
   care apar in aceasta supraincarcare se va lua in considerare noua functie;
  de exemplu in program se putea adauga functia:

   void swap(int &x, int &y){x=x+y; y=x-y; x=x-y;}

   atunci pentru z=max(x,y) se folosea automat aceasta functie si nu o
   instantiere a funtiei template;
  asemenea supraincarcatri explicite se fac atunci cand pentru anumite tipuri
   de date se doreste aplicarea unui alt algoritm decat cel general rezultat
   din functia template (in absenta acestei supraincarcari s-ar genera
   automat o instanta a functiei template care aplica algoritmul general);

- functiile template se folosesc de regula atunci cand pentru mai multe
   tipuri de date algoritmul este acelasi; daca algoritmul difera de la un
   tip de date la altul, se folosesc numai supraincarcari explicite;
  de exemplu daca am dori sa scriem o functie

   int poz(t x)

   care primind ca parametru o data x de un tip t sa returneze numarul de
   caractere din reprezentarea externa a lui x (numarul de caractere prin care
   se scrie x pe ecran), atunci pentru x de tip int, double, sir, algoritmul
   de calcul ar diferi; astfel, in loc de o functie template:

   <class t>int poz(t x){.....}

   se vor scrie in program 3 supraincarcari explicite:

   int poz(int x){.....}
   int poz(double x){.....}
   int poz(sir x){.....}

- restrictii pentru functiile template:
  o functie virtuala nu poate fi template;
  destructorii nu pot fi template;
*/