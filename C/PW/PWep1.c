#include <stdio.h>
int main()
{
    // basics
    printf("check");
    printf("\nnewline tech\n\n");

    // variables
    int x;
    x = 5;
    printf("%d", x);
    x = x + 5;
    printf("\n%d", x);

    // arithmetic
    int y;
    y = 5;
    printf("\n\n%d", x + y);
    printf("\n%d\n", x - y);
    printf("%d\n", x * y);
    printf("%d", x / y);

    // arithmetic in variable declaration
    int z;
    z = x + y;
    printf("\n\n%d", z);

    // floats
    float a;
    a = 3.1418;
    printf("\n\n%f", a);
    // float arithmetic
    printf("\n\n%f", a + x);

    // float and int arithmetic datatype exceptions
    float b = 5 / 2;
    printf("\n\n%f", b);
    b = 5.0 / 2;
    printf("\n%f", b);
    b = 5 / 2.0;
    printf("\n%f", b);

    // alternate variable decleration
    int p, q, r, s;
    p = 5;
    q = 6;
    r = 7;
    s = 8;
    printf("\n\n%d %d %d %d", p, q, r, s);

    // input syntax
    // float c;
    // printf("\n\nEnter value of variable c: ");
    // scanf("%f", &c);
    // printf("\nValue of variable c is: %f", c);

    // multiple input
    // float d, e;
    // scanf("%f%f", &d, &e);

    // modulo operator (remainder)
    float remainder = x / y;
    printf("\n\nremainder when %d is divided by %d is %f", x, y, remainder);

    // char datatype
    char ch = 'a';
    printf("\n\n%c", ch);

    return 0;
}