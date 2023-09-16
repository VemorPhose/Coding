#include <stdio.h>
// fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)
int fibonacci(int n)
{
    if (n == 1 || n == 2)
        return 1;
    int s = fibonacci(n - 1) + fibonacci(n - 2);
    return s;
}
int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", fibonacci(x));
    return 0;
}