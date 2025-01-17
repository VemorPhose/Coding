#include <stdio.h>
int main()
{
    int x, y, z;
    printf("enter starting number: ");
    scanf("%d", &x);
    printf("enter increment: ");
    scanf("%d", &y);
    printf("enter number of elements: ");
    scanf("%d", &z);

    for (int i = x; i <= x + (z - 1) * y; i = i + y)
    {
        printf("%d ", i);
    }

    return 0;
}