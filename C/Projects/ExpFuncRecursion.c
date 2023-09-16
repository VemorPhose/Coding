#include <stdio.h>
int expo(int a, int n)
{
    if (n == 1)
    {
        return a;
    }
    int s = a * expo(a, n - 1);
    return s;
}
int main()
{
    printf("a: ");
    int x;
    scanf("%d", &x);
    printf("n: ");
    int y;
    scanf("%d", &y);
    printf("%d", expo(x, y));
    return 0;
}