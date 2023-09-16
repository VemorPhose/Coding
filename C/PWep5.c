#include <stdio.h>
#include <math.h> //math function library
// power function
int power(int a, int b)
{
    int c = 1;
    for (int i = 1; i <= b; i++)
    {
        c *= a;
    }
    return c;
}
int main()
{
    // calling power function
    // printf("enter base: ");
    // int x;
    // scanf("%d", &x);
    // printf("enter power: ");
    // int y;
    // scanf("%d", &y);

    // printf("%d", power(x, y));

    // library functions ( inbuilt functions )  --  printf(), scanf(), sqrt()
    printf("\n%f", sqrt(35));

    // library function from math
    printf("\n%f", pow(25, 2));

    // pointers
    int x = 5;
    printf("\n\n%d", x);
    printf("\n%p", &x); // %p is identifier for pointers, datatype of pointers is int*

    // storing address of pointers
    int *a = &x;
    // or,
    int *b = &x; // basically, putting * in front of variable is a toggle between value and address of variable
    // an example of * usage
    printf("\n\n%p", a); // prints a, i.e. pointer
    printf("\n%d", *a);  // prints opposite of a, i.e. int

    // pass by value
    // func ( a, b );

    // pass by reference
    // func ( &a, &b );

    // pass by value will not update the actual variables outside the function and any updates will only
    // affect local variables within the function to which the global variables' values have been passed
    // to. On the other hand, pass by reference will bring any local changes within the function to the
    // variables will change the global variables themselves.

    // check project file titled pointerr

    // double pointer
    int **c = &a; // int** is datatype for variable storing pointer for int* datatype.

    // triple pointer
    int ***d = &c; // int*** is datatype for variable storing pointer for int** datatype.

    // fetching value from double ( or more ) pointers
    printf("\n%p", &c);  // address of double pointer
    printf("\n%p", c);   // address of pointer
    printf("\n%p", *c);  // address of variable
    printf("\n%d", **c); // value of variable
    // more number of *, deeper dive into fetching value from pointer chain.

    return 0;
}