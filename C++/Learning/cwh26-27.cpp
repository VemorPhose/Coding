#include <iostream>
using namespace std;

// forward declaration
class complex;

class calculator{
    public:
    int add(int a, int b){
        return(a + b);
    }

    int sumRealComplex(complex , complex ); // not declaring variable names yet as class not declared yet.
    int sumCompComplex(complex , complex );
};

class complex{
    int a;
    int b;

    public:
        void setData(int r, int c){
            a = r;
            b = c;
        }

        void setDataBySum(complex n1, complex n2){
            a = n1.a + n2.a;
            b = n1.b + n2.b;
        }

        // friend function declaration.
        friend complex setDataBySumFriend(complex n1, complex n2);

        // friend function from another class declaration.
        friend int calculator :: sumRealComplex(complex n1, complex n2);
        friend int calculator :: sumCompComplex(complex n1, complex n2);

        // whole ass friend class declaration.
        friend class calculator;

        void printNumber(void){
            cout << "value of this complex is " << a << " + " << b << "i" << endl;
        }
};

// external function that can access private data of class objects.
complex setDataBySumFriend(complex n1, complex n2){
    complex c;
    c.setData(n1.a + n2.a, n1.b + n2.b);
    return c;
}

int calculator :: sumRealComplex(complex n1, complex n2){ // scope resolution operator to define as part of class later
        return(n1.a + n2.a);
}

int calculator :: sumCompComplex(complex n1, complex n2){
        return(n1.b + n2.b);
}

int main(){
    complex c1, c2, c3, c4;
    c1.setData(1, 2);
    c2.setData(3, 4);

    c3.setDataBySum(c1, c2);
    c4 = setDataBySumFriend(c1, c2); // friend functions cannot be called as an attribute of class object
    // i.e. c4.setDataBySumFriend() does not work.

    c3.printNumber();
    c4.printNumber();

    calculator calc;
    int resultReal = calc.sumRealComplex(c1, c2);
    cout << "sum of real parts are " << resultReal << endl;
    cout << "sum of complex parts are " << calc.sumCompComplex(c1, c2) << endl;
    return 0;
}