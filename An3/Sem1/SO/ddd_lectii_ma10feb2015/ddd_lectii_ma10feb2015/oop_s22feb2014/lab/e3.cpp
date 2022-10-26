#include<iostream>

class MyExceptionBase{
    virtual char const * message() const = 0;
  public:    
    void show();
};
void MyExceptionBase::show() {std::cout << message() << std::endl;}

class MyException1: public MyExceptionBase{
    char const * message() const;
};
char const * MyException1::message() const {return "Text 1";}

class MyException2: public MyExceptionBase{
    char const * message() const;
};
char const * MyException2::message() const {return "Text 2";}

int main(){
   for(int i = 0; i < 3; ++i)  
       try {
           switch (i) {
             case 0: throw MyException1 ();
             case 1: throw MyException2 ();
             case 2: new int[1000000000];
           } 
    
       }
       catch (MyExceptionBase &e) {
           e.show();    
       }
       catch (std::exception &e) {
           std::cout << e.what() << std::endl;
       }
}

/*
Afisaza:

Text 1
Text 2
std::bad_alloc
*/
