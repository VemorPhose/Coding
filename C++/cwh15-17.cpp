#include <iostream>
using namespace std;

int summation(int a, int b){ // function definition, in global space. a and b here are formal parameters.
    return(a+b);
}

void greet(void){ // outer void means it returns nothing, inner void means it accepts nothing. can also write () instead of (void).
    cout << "Hello World" << endl << "Blank Line" << endl;
}

void check(); // calling function defined after main block, before the main block to bring into scope of main block.

// call by value
int swapvalue(int a, int b){ // call by value
    int temp = a;
    a = b;
    b = temp;
    cout << a << endl << b << endl;
    return 0;
}

// call by reference - using pointers/addresses
int swappointer(int *a, int *b){ // call by reference - using pointers/addresses
    int temp = *a;
    *a = *b;
    *b = temp;
    cout << *a << endl << *b << endl;
}

// call by reference - using c++ reference
int & swapreference(int &a, int &b){ // UNDERSTAND AND MEMORIZE SYNTAX.
    int temp = a;
    a = b;
    b = temp;
    cout << a << endl << b << endl;
}

// inline functions
// replaces function call with the code within to make the program run quicker. 
// only useful when the function contents are minimal and the function serves a readability purpose.
inline int product(int a, int b){
    return a*b;
}
// recommended not to use inline functions with recurring functions, static variables, loops, switch statements, etc.

// static variables
void staticvar(){
    static int perma = 0; // variable is not closed after function call is finished. 
    // moreover, if function is called multiple times, value of static var will be retained.
}

// default arguments
int defaultarg(int a, int b = 50){ // 50 is default value of b. NON-DEFAULT ARGS MUST NEVER COME AFTER DEFAULT ARGS.
    return(a+b);
}

// constant argument - such that argument passed is not modified inside the function. Usually used with pointers.
int constarg(const int a){ // const specifies that passed variable cannot be modified.
    return a;
}

int main(){
    int a = 2, b = 3;
    cout << summation(a, b) << endl; // a and b here are actual parameters.
    // formal parameters a and b will be taking values from actual parameters a and b
    greet();
    check();

    int num1 = 2, num2 = 3;
    swapvalue(num1, num2); // call by value, inner variables will be swapped but not in main block
    cout << num1 << endl << num2 << endl;
    swappointer(&num1, &num2); // call by pointer, inner as well as main block variables will be swapped.
    cout << num1 << endl << num2 << endl;
    swapreference(num1, num2); // call by reference, inner as well as main block variables will be swapped.
    cout << num1 << endl << num2 << endl;

    cout << product(num1, num2) << endl; // inline function call

    return 0;
}

void check(){ // function declared after main block, will give scope error when running. function needs to be called before the main function without contents to bring into scope.
    cout << "check" << endl;
}