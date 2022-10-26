#include<iostream.h>
#include<string.h>

class string{
  char *s;
 public:
  void set(char *);
  void get(char *, int);
  char &operator[](int);
  string& operator=(string&);
};

string& string::operator=(string& x){
  delete []s;                          /* noutate */
  s=new char[strlen(x.s)+1];
  strcpy(s,x.s);
  return *this;
}

void string::set(char *ps){
  delete []s;                          /* noutate */
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

/* Acum in metodele "set" si "operator=" se dezaloca zona pointata anterior
 de "s", dar la prima folosire a obiectului ce dezaloca "delete" ? De
 asemenea, cine dezaloca zona pointata de "s" dupa ultima folosire a
 obiectului (presupunand ca programul nu se termina - de exemplu obiectul
 este alocat automatic intr-o functie) ?
   Ar trebui ca obiectele string sa fie initializate automat cu "s" NULL
 inainte de prima folosire si sa li se dezaloce automat "s" dupa ultima
 folosire.
   Acest program nu trebuie rulat, deoarece produce efecte imprevizibile.
*/
