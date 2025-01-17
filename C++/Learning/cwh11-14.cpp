#include <iostream>
using namespace std;
int main(){
    // break, continue.

    // pointers - datatype which holds address of other datatypes
    int a = 3;
    int *b = &a; // * ---> Dereference operator, & ---> (Address of) operator
    cout << &a << endl << b << endl; // both will print the address of a.
    cout << a << endl << *b << endl; // both will print value of a, i.e. value at pointer b.

    // double pointer
    int **c = &b;
    cout << c << endl; // address of b
    cout << *c << endl; // b, i.e. address of a
    cout << **c << endl; // value of a.

    // arrays
    int arr1[] = {4, 5, 6, 7};
    int arr2[4];
    for(int i = 0; i <= 3; i++){
        arr2[i] = i;
    }

    // int *p = &arr1; ---> WRONG, array itself is a pointer of its first block.
    int *p = arr1; // p will now store pointer of arr[0]
    
    // pointer arithmetic.
    cout << arr1[0] << endl << *p << endl; // prints value at 0th index of arr1
    cout << arr1[1] << endl << *(p+1) << endl; // prints value at 0+1 = 1st index of arr1
    cout << arr1[2] << endl << *(p+2) << endl; // prints value at 0+2 = 2nd index of arr1
    cout << arr1[3] << endl << *(p+3) << endl; // prints value at 0+3 = 3rd index of arr1

    // structures
    typedef struct employee // custom datatype with nested datatypes
    {
        int eId;
        string eName;
        float eSal;
    } emp; // renaming so as to not type "struct employee" before defining new variable every time.
    
    emp ram;
    ram.eId = 1;
    ram.eName = "ram";
    ram.eSal = 50;

    // unions
    union money // struct but ONLY ONE NESTED VARIABLE AT A TIME CAN BE USED.
    {
        int dollar;
        float euro;
        double inr;
    } car; // inline variable declaration with same datatype.

    car.dollar = 5; // car.dollar is inputted
    car.euro = 6.0; // car.dollar is deleted and becomes garbage value, euro is inputted.

    // enum
    enum Meal { breakfast, lunch, dinner }; // assigns value 0, 1, 2 to the words inside.
    cout << breakfast << lunch << dinner << endl; // couts 012.
    // this increases code readability.

    return 0;
}