#include <iostream>
#include <iomanip> // library function for manipulators such as setw, endl, etc.
using namespace std;

int glob = 10; // global variable

int main()
{
    int num1, num2;
    cout << "test" << endl;
    cout << "endl works when 'using namespace std'" << endl; // endl working

    // arithmetic operators : +, -, *, /, %
    // increment operators : a++, a--, ++a, --a
    // comparison operators : >, <, ==, >=, <=
    // logical operators : &&, ||

    int glob = 5; // local variable
    cout << glob << endl; // local output
    cout <<::glob << endl; // global output, :: is scope resolution operator.

    // character as a suffix to a value acts as a datatypecaster.
    cout << sizeof(34.5f) << endl; // 34.5f is a float. F or f both work.
    cout << sizeof(34.5) << endl; // by default 34.5 is a double. D or d both work.
    cout << sizeof(34.5l) << endl; // 34.5l is a long double. L or l both work.

    // typecasting
    cout << (float)num1 << endl; // traditional c, works
    cout << float(num1) << endl; // python style, also works

    // reference variables
    float x = 45.0;
    float &y = x; // y is a shallow copy of x.
    cout << y << endl << x << endl;    

    // constants
    const int PI = 3.1416; // const keyword makes the variable read only

    // manipulatorsa - help control data display
    // example - endl, setw
    int a = 3, b = 76, c = 1234;
    cout << setw(4) << a << endl;
    cout << setw(4) << b << endl;
    cout << setw(4) << c << endl; // prints all numbers with a width of 4, i.e. they appear right justified.
    
    // if, else if, else

    // switch statement
    int s = 0;
    switch (s)
    {
    case 0:
        cout << "a" << endl;
    case 1:
        cout << "b" << endl;
    case 2:
        cout << "c" << endl;
    
    default:
        break;
    }

    // for loops, while loops

    // do-while
    int i = 1;
    do{
        cout << i << endl;
        i++;
    } while(i <= 3);

    return 0;
}