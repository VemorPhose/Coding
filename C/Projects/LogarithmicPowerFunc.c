#include <stdio.h>
int logpow(int a, int n)
{
    if (n == 1)
        return a;
    else if (n % 2 != 0)
    {
        return a * logpow(a, n - 1);
    }
    else
        return logpow(a, n / 2) * logpow(a, n / 2);
}
int main()
{
    printf("enter a: ");
    int a;
    scanf("%d", &a);
    printf("enter n: ");
    int n;
    scanf("%d", &n);
    printf("%d to the power %d is %d", a, n, logpow(a, n));
    return 0;
}