#include <iostream>
using namespace std;

// constructors
class Complex{
    int r;
    int c;
    public:
        // Creating a constructor.
        // It is basically a function with the same name as the class.
        // it is used to initialize objects of its class.
        // it is automatically invoked when an object is declared with the class name.
        // MUST BE DECLARED IN PUBLIC.
        Complex(void); // Constructor declaration

        void printNumber(void){
            cout << "your number is " << r << " + " << c << 'i' << endl;
        }

}; // always rember semicolon after class declaration.

Complex :: Complex(void){ // this is called a DEFAULT CONSTRUCTOR as it takes no parameters.
    r = 0;
    c = 0;
}

int main(){
    Complex num1;
    num1.printNumber();
    return 0;
}