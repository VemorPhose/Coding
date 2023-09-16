#include <stdio.h>
void printer(int i, int n)
{
    if (i == n + 1)
    {
        return;
    }
    printf("%d ", i);
    printer(i + 1, n);
}
void techyprinter(int n)
{
    if (n == 0)
    {
        return;
    }
    techyprinter(n - 1);
    printf("%d ", n);
}
int main()
{
    int x;
    printf("enter n: ");
    scanf("%d", &x);
    printer(1, x);
    printf("\n\n");
    techyprinter(x);
    return 0;
}