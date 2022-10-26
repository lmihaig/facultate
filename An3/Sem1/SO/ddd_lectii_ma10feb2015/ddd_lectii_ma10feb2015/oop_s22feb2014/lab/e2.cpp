#include<iostream>
using namespace std;

void f(int, int);

void g(int n, int p) {
    if (n < 12) f(n, p);
    else switch(p % 3) {
        case 0: throw 10;
        case 1: throw 3.14;
        case 2: throw "abc";
    }
}

void f(int n, int p){
    switch (n % 3) {
        case 0: try {
                   g(n + 1, p);
                } catch (int x) {
                   cout << "Am prins int: " << x << ", n = " << n << endl;
                   throw;
                }
        case 1: try {
                   g(n + 1, p);
                } catch (double x) {
                   cout << "Am prins double: " << x << ", n = " << n << endl;
                   throw;
                }
        case 2: try {
                   g(n + 1, p);
                } catch (char const * x) {
                   cout << "Am prins sir : " << x << ", n = " << n << endl;
                   throw;
                }
    }
}

int main(){
  try {f(0, 0);} catch(...) {} cout << endl;
  try {f(0, 1);} catch(...) {} cout << endl;
  try {f(0, 2);} catch(...) {} cout << endl;
}

/*
Afisaza:

Am prins int: 10, n = 9
Am prins int: 10, n = 6
Am prins int: 10, n = 3
Am prins int: 10, n = 0

Am prins double: 3.14, n = 10
Am prins double: 3.14, n = 7
Am prins double: 3.14, n = 4
Am prins double: 3.14, n = 1

Am prins sir : abc, n = 11
Am prins sir : abc, n = 8
Am prins sir : abc, n = 5
Am prins sir : abc, n = 2
*/
