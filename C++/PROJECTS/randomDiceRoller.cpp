#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main(){
    srand(static_cast<unsigned int>(time(0))); // seeds random number generator based on present date and time.
    int randomNum = rand();
    randomNum = randomNum % 6 + 1; // gives random number from 1 to 6.
    cout << "You rolled a " << randomNum << endl;
    cout << RAND_MAX << " is the max value given by rand() function." << endl;
    return 0;
}