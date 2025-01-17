// https://www.codecademy.com/courses/c-plus-plus-for-programmers/articles/reference-and-pointers-cpp
#include <iostream>
#include <string>
using namespace std;
int main(){
    // references
    int a;
    int & b = a; // b is just an alias for a.
    // int c = & a; does not work.

    b = 10; // a also gets changed
    cout << a << endl;

    // note: 
    // 1. references cannot be assigned to uninitialized variables.
    // 2. references should not be reassigned. Bakchodi hoti hai.

    // applications:
    // 1. in function formal parameters, to pass by reference so that the original variable also gets modified.
    // 2. when not used in declaration, & is known as the ADDRESS OF operator, used to access memory address of a variable.
    cout << &a << endl;

    // pointers
    int * c; // int * means pointer to an int variable.
    // assignment to a pointer variable is usually through a reference (memory address)
    int d = 15;
    c = & d; // c is nothing but a pointer pointing to address of d. Thus, d == * c and c == & d.
    cout << * c << endl;
    cout << c << ' ' << & d << endl;

    // when not used in declarations, * is used as dereference operator, to obtain value from the pointer.

    // to declare pointer with no address to point towards, use nullptr.
    string * e = nullptr;

    return 0;
}