#include <stdio.h>
int factorial(int g)
{
    int a = 1;
    for (int i = 1; i <= g; i++)
    {
        a *= i;
    }
    return a;
}
int main()
{
    int n, r;
    printf("n: ");
    scanf("%d", &n);
    printf("r: ");
    scanf("%d", &r);

    printf("nCr is: %d", (factorial(n) / (factorial(n - r) * factorial(r))));

    return 0;
}