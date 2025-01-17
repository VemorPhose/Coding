#include <stdio.h>
int factorial(int a)
{
    if (a == 1)
    {
        return 1;
    }
    int fact = a * factorial(a - 1);
    return fact;
}
int main()
{
    printf("enter int: ");
    int x;
    scanf("%d", &x);
    printf("factorial is: %d", factorial(x));
    return 0;
}