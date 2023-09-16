#include <stdio.h>
int main()
{
    int a = 5;
    int b = 6;
    int c = 7;
    if (a > b && a > c)
    {
        printf("%d is greatest", a);
    }
    else if (b > a && b > c)
    {
        printf("%d is greatest", b);
    }
    else if (c > b && c > b)
    {
        printf("%d is greatest", c);
    }
    else
    {
        printf("numltiple inputs equivalent");
    }

    return 0;
}