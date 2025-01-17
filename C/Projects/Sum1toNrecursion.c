#include <stdio.h>
int summer(int n, int s)
{
    if (n == 0)
    {
        return s;
    }
    // s += n;
    summer(n - 1, s + n);
}
int factorialesque_summer(int n)
{
    if (n == 1)
    {
        return 1;
    }
    int s = n + factorialesque_summer(n - 1);
    return s;
}
int main()
{
    printf("n: ");
    int x;
    scanf("%d", &x);
    printf("%d", summer(x, 0));
    printf("\n%d", factorialesque_summer(x));
    return 0;
}