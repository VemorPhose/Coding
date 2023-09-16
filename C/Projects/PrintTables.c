#include <stdio.h>
int main()
{
    int x;
    printf("Enter number for which tables are to be printed: ");
    scanf("%d\n", &x);
    printf("%d\n", x);
    for (int i = 1; i <= 10; i++)
    {
        printf("%d\n", (x * i));
    }
    return 0;
}