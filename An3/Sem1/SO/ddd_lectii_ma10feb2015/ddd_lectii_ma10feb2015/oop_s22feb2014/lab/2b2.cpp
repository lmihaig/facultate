#include<iostream.h>
#include<string.h>

class string{
  char *s;
 public:
  void set(char *);
  void get(char *, int);
  char &operator[](int);
  string& operator=(string&);          /* noutate */
};

string& string::operator=(string& x){  /* noutate */
  s=new char[strlen(x.s)+1];           /* noutate */
  strcpy(s,x.s);                       /* noutate */
  return *this;                        /* noutate */
}

void string::set(char *ps){
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

void main(){
  cout<<"--------------------\n";
  string a,b; char buf[100];
  a.set("abc");
  a.get(buf,100); cout<<buf<<endl;
  b=a; b[1]='x'; a.get(buf,100); cout<<buf<<endl;
}

/* Operatorul de atribuire definit de noi este OK;
   Dar in metodele "set" si "operator=" nu se dezaloca zona pointata
    anterior de "s" si astfel la un moment dat se poate umple memoria.
*/
