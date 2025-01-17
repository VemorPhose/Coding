#include <stdio.h>
int main()
{
    // if-else
    int a;
    printf("Enter an int: ");
    scanf("%d", &a);
    // even-odd if-else example
    int rem = a % 2;
    if (a == 619)
    {
        printf("Enter password: ");
        scanf("%d", &a);
        if (a == 911)
        {
            printf("\naccess granted");
        }
    }
    else if (rem == 1)
    {
        printf("inputted int is odd");
    }
    else
    {
        printf("inputted int is even");
    }

    // multiple conditions
    // if(a>b && a>c){printf("unga bunga")}

    // ternary operator
    // expression1 ? expression2 : expression3
    // i.e. condition ? if_code : else_code

    a % 2 == 0 ? printf("\neven number") : printf("\nodd number");

    // if test
    if (a = 6)
    {
        printf("\nWORKS");
    }

    return 0;
}