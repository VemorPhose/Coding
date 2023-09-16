#include <iostream>
#include <math.h>
using namespace std;

class Complex{
    int r;
    int c;

    friend void distComplex(Complex, Complex);
    public:
        Complex(int a, int b);

        void printNumber(void){
            cout << "your number is " << r << " + " << c << 'i' << endl;
        }

};

Complex :: Complex(int a = 0, int b = 0){ // parameterized constructor
    r = a;
    c = b;
}

void distComplex(Complex c1, Complex c2){
    int xdist = c1.r - c2.r;
    int ydist = c1.c - c2.c;
    cout << "distance between two complex points is " << sqrt(xdist * xdist + ydist * ydist) << endl;
}

int main(){
    // implicit call
    Complex num1(4, 6);

    // explicit call
    Complex num2 = Complex(5, 7);

    // default values of parameters of constructor.
    Complex num3;

    num1.printNumber();
    num2.printNumber();
    num3.printNumber();

    distComplex(num1, num2);
    return 0;
}