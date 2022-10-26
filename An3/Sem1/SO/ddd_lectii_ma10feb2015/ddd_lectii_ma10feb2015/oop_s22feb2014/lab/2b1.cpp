// stringuri cu tentativa de atribuire

#include<iostream.h>
#include<string.h>

class string{
  char *s;
 public:
  void set(char *);
  void get(char *, int);
  char &operator[](int);
};

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

/* Observam ca exista un operator predefinit de atribuire,
  dar el nu e bun aici deoarece copiaza bit cu bit membrii
  declarati (locatia obiectului) - deci nu duplica zona
  pointata de "a.s".
*/
