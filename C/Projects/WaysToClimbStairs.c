#include <stdio.h>
int factorial(int n)
{
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}
int nCrSummation(int n, int r)
{
    if (r == 0)
        return 1;
    int s = factorial(n) / (factorial(n - r) * factorial(r)) + nCrSummation(n, r - 1);
    return s;
}
int techystaircounter(int n)
{
    if (n == 1)
    {
        return 1;
    }
    int s = 2 * techystaircounter(n - 1);
    return s;
}
int main()
{
    printf("enter number of stairs to climb: ");
    int x;
    scanf("%d", &x);
    printf("number of ways to climb %d stairs are: %d", x, nCrSummation(x - 1, x - 1));
    printf("\nnumber of ways to climb %d stairs are: %d", x, techystaircounter(x));

    return 0;
}