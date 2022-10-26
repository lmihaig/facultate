#include<iostream>
#include<exception>
#include<csignal>

class X {};
class Y {};
class Z : public X {};
class W {};
 
void f(int n) throw(X, Y) 
{
  if (n == 0) throw X(); // OK
  if (n == 1) throw Z(); // OK
  try{throw W();} catch (...) {} // OK (exceptia e prinsa in functie)
  throw W(); 
    // apeleaza 'std::unexpected()',
    // care implicit apeleaza 'std::terminate',
    // care implicit apeleaza 'std::abort.',
    // care trimite procesului semnalul SIGABRT,
    // apoi procesul se termina anormal
}

void u_handler () {std::cout << "Unexpected !\n";}

void t_handler () {std::cout << "Terminated !\n";}

void s_handler (int n) {std::cout << "Signal " << n << std::endl;}

int main () {
    std::set_unexpected(u_handler);
    // de acum incolo 'std::unexpected()' apeleaza 'u_handler'
    std::set_terminate(t_handler);
    // de acum incolo 'std::terminate()' apeleaza 't_handler'
    signal(SIGABRT, s_handler);
    // de acum incolo la primirea semnalului SIGABRT se apeleaza 's_handler'

    int x; std::cin >> x;

    switch (x) {
      case 0: throw 10;
      case 1: for(int i = 0; i < 3; ++i)
                  try { f(i); }
                  catch(X &e) {std::cout << "Prins X\n";}
                  catch(Y &e) {std::cout << "Prins Y\n";}
                  catch(Z &e) {std::cout << "Prins Z\n";}
                  catch(W &e) {std::cout << "Prins W\n";}
                  catch(std::exception &e)
                    {std::cout << "Prins " << e.what() << std::endl;}
              break;
    }          
}

/*
La compilare se afisaza:

  In function ‘int main()’:
    warning: exception of type ‘Z’ will be caught
    warning:    by earlier handler for ‘X’
    
La rulare, daca introducem '0' se afisaza:    

  Terminated !
  Signal 6
  Aborted

iar daca introducem '1' se afisaza:

  Prins X
  Prins X
  Unexpected !
  Terminated !
  Signal 6
  Aborted
*/
