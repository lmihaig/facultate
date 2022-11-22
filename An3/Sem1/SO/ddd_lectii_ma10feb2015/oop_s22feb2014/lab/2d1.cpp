// stringuri cu atribuire si
//   tentativa de initializare prin copiere si de transmitere prin valoare

#include<iostream.h>
#include<string.h>

class string{
  char *s;
 public:
  string();
//  ~string();      /* temporar, eliminam destructorul */
  void set(char *);
  void get(char *, int);
  char &operator[](int);
  string& operator=(string&);
};

string::string(){
  s=NULL;
}

//string::~string(){
//  delete []s;
//}

string& string::operator=(string& x){
  delete []s;
  s=new char[strlen(x.s)+1];
  strcpy(s,x.s);
  return *this;
}

void string::set(char *ps){
  delete []s;
  s=new char[strlen(ps)+1];
  strcpy(s,ps);
}

void string::get(char *ps, int d){
  strncpy(ps,s,d);
  if(d>0)ps[d-1]='\0';
}

char& string::operator[](int i){
  return s[i];
}

void f(string x){ // parametru prin valoare /* noutate */
  x[1]='z';                                 /* noutate */
}                                           /* noutate */

void main(){
  cout<<"--------------------\n";
  string a; char buf[100];                  /* noutate */
  a.set("abc");                             /* noutate */
  string b=a;                               /* noutate */
  b[1]='x';                                 /* noutate */
  a.get(buf,100); cout<<buf<<endl;          /* noutate */
  string c=a;                               /* noutate */
  f(c);                                     /* noutate */
  a.get(buf,100); cout<<buf<<endl;          /* noutate */
}

/* Observatii:
 - definirea cu initializare dintr-un obiect de acelasi tip (copiere) sau
  transmiterea prin valoare utilizeaza o metoda de copiere alta decat
  operatorul de atribuire - este de fapt un constructor de copiere;
 - exista un constructor de copiere predefinit, dar el nu e bun aici
  deoarece copiaza bit cu bit membrii declarati (la fel ca si operatorul
  predefinit de copiere) - deci nu duplica zona pointata de "a.s" sau "c.s";
 - deoarece obiectele de tip "string" "a", "b", "c" si "x" ajung sa
  pointeze prin membrii lor "s" aceeasi zona, destructorii acestora ar
  provoca tentativa de a dezaloca de mai multe ori zona respectiva cu
  "delete", ceea ce ar produce efecte imprevizibile (de regula terminarea
  anormala a programului); de aceea, pentru a se putea rula acest program,
  destructorul definit de utilizator a fost eliminat.
*/
