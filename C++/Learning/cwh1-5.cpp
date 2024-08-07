#include <iostream>

int main() {
  
    std::cout << "Hello World!\n"; // std::cout is the “character output stream”
    // << is called extraction operator, >> is called insertion operator
    int score = 0; // variable declaration
    std::cin >> score; // input statement

    /* multi line
    comment */

    std::cout<<"score = "<<score<<"\n"; //inline printing tech
    int a; // int
    float b; // 6 decimal places
    char c; // single byte, single character
    double d; // 15 decimal places
    bool e; // boolean


    // user defined variables : struct, union, enum
    // derived variables : array, function, pointer

    // endl can be used instead of "\n" in cout. Does not work here for some reason.

    

    return 0;
}