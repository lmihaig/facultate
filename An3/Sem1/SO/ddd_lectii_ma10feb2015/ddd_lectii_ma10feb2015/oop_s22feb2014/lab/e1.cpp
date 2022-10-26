#include<iostream>
using namespace std;

int main(){
  
    try {
      
        cout << "Incepe try exterior\n\n";  
      
        for(int i = 0; i < 4; ++i) {
            cout << "Incepe iteratia nr. " << i << endl;
            try{
                cout << "Incepe try interior\n";
                switch(i){
                    case 1: throw 10;
                    case 2: throw 3.14;
                    case 3: throw "Un sir";
                }
                cout << "Se termina try interior\n";
            } catch(double x) {
                cout << "Am prins valoarea de tip double: " << x << endl;
            } catch(int n) {
                cout << "Am prins valoarea de tip int: " << n << endl;  
            } catch(...) {
                cout << "Am prins o valoarea de alt tip.\n";  
                throw;
            }
            cout << "Se termina iteratia nr. " << i << endl << endl;;
        }
      
        cout << "\nSe termina try exterior\n";
    
    } catch (int x) {
        cout << "Am prins in exterior valoarea de tip int: " << x << endl;  
    } catch (char const *s) {
        cout << "Am prins in exterior sirul constant: " << s << endl;    
    }
}

/*
Afisaza:

Incepe try exterior

Incepe iteratia nr. 0
Incepe try interior
Se termina try interior
Se termina iteratia nr. 0

Incepe iteratia nr. 1
Incepe try interior
Am prins valoarea de tip int: 10
Se termina iteratia nr. 1

Incepe iteratia nr. 2
Incepe try interior
Am prins valoarea de tip double: 3.14
Se termina iteratia nr. 2

Incepe iteratia nr. 3
Incepe try interior
Am prins o valoarea de alt tip.
Am prins in exterior sirul constant: Un sir
*/
