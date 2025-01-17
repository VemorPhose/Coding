#include <stdio.h>
void printer(int a)
{
    if (a == 0)
    {
        return;
    }
    printf("%d ", a);
    printer(a - 1);
}
int main()
{
    printf("n to 1: ");
    int n;
    scanf("%d", &n);
    printer(n);
    return 0;
}