#include <iostream>
using namespace std;

// recursion
int factorial(int a){
    if(a <= 1) return 1; // base condition
    return a*factorial(a-1); // logic, n! = n*(n-1)!
}

// when coding a recursive function, two things to think about.
// 1. logic to use the function recursively.
// 2. base case to end recursion loop.

int fibonaccinth(int n){
    // f(n) = f(n-1) + f(n-2)
    if(n == 1 || n == 2) return 1;
    return (fibonaccinth(n-1) + fibonaccinth(n-2));
}

// function overloading - multiple functions with same name but different number of args.

// for overloading, either one must be true:
// 1. different datatypes of the formal parameters
// 2. different number of formal parameters

int sum(float a, int b){ // fn with two args
    return(a+b);
}

int sum(int a, int b, int c){ // fn with three args
    return(a+b+c);
}

int volume(float r, float h){
    return(3.14 * r * r * h);
}

int main(){
    cout << factorial(5) << endl;
    cout << fibonaccinth(5) << endl;

    cout << sum(2,3) << endl; // even if datatype in formal argument is float and in actual arg is int, it is converted and no error shown.
    cout << sum(2,3,4) << endl; // functions are picked up automatically even though same name.

    cout << volume(2,3) << endl;
    return 0;
}