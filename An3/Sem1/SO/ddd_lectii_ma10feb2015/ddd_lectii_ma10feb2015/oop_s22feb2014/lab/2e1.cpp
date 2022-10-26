// stringuri cu atribuire,
// initializare prin copiere si transmitere prin valoare,
// intializare prin conversie si transmitere prin valoare
//   a unei valori de alt tip OK

#include<iostream.h>
#include<string.h>

class string{
  char *s;
 public:
  string(string&);
  string(char *);            /* noutate */
  string();
  ~string();
  void set(char *);
  void get(char *, int);
  char &operator[](int);
  string& operator=(string&);
};

string::string(char *ps){    /* noutate */
  s=new char[strlen(ps)+1];  /* noutate */
  strcpy(s,ps);              /* noutate */
}                            /* noutate */

string::string(string &x){
  s=new char[strlen(x.s)+1];
  strcpy(s,x.s);
}

string::string(){
  s=NULL;
}

string::~string(){
  delete []s;
}

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

void f(string x){ // parametru prin valoare
  x[1]='z';
}

void main(){
  cout<<"--------------------\n";
  char buf[100];
  string a="abc";  // se poate scrie echivalent: string a("abc"); /* noutate */
  a.get(buf,100); cout<<buf<<endl;                                /* noutate */
  f("123");                                                       /* noutate */
}

/* Nu exista constructor de conversie predefinit - in absenta celui definit
     de noi s-ar semnala eroare la compilare.
*/
