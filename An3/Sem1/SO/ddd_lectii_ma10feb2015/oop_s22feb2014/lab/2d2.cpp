// stringuri cu atribuire,
// initializare prin copiere si transmitere prin valoare OK

#include<iostream.h>
#include<string.h>

class string{
  char *s;
 public:
  string(string&);           /* noutate */
  string();
  ~string();
  void set(char *);
  void get(char *, int);
  char &operator[](int);
  string& operator=(string&);
};

string::string(string &x){   /* noutate */
  s=new char[strlen(x.s)+1]; /* noutate */
  strcpy(s,x.s);             /* noutate */
}                            /* noutate */

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
  string a; char buf[100];
  a.set("abc");
  string b=a;    // se poate scrie echivalent: string b(a);
  b[1]='x';
  a.get(buf,100); cout<<buf<<endl;
  string c=a;    // se poate scrie echivalent: string c(a);
  f(c);
  a.get(buf,100); cout<<buf<<endl;
}
