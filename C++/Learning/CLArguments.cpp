// https://www.codecademy.com/courses/c-plus-plus-for-programmers/articles/command-line-arguments-cpp
#include <iostream>
using namespace std;

// while compiling the program with g++ CLArguments.cpp -o CLArguments:
// when it is run using ./CLArguments, additional arguments can be passed in the command.
// such as ./CLArguments Hello World
// multiple arguments need to be separated by spaces.

int main(int argc, char * argv[]){ // in order to access command line arguments, main function takes two more arguments.
// can also be (int argc, char ** argv).
    // argc --> argument count:
    // is an int parameter containing the number of command line arguments passed to the program. 
    // The value of argc is at least 1 because the name of the executable is treated as an argument.

    // argv --> argument vector:
    // is an array parameter containing the values of command line arguments. The range of argv spans from 0 to argc - 1.

    // note: argv[0] is always the name of the executable (./CLArguments).
    for(int i = 0; i < argc; i++){
        cout << "argv[" << i << "] : " << argv[i] << endl;
    }

    // note: to pass an argument with a space in it, use " ".
    // note: to pass an argument with ", use \".
    
    return 0;
}