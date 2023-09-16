#include <stdio.h>
int main()
{
    int a = 7;
    int b = 9;
    int c = 11;

    if (a > b)
    {
        if (c < b)
        {
            printf("%d is least", c);
        }
        else
            printf("%d is least", b);
    }
    else if (a < b)
    {
        if (c < a)
        {
            printf("%d is least", c);
        }
        else
            printf("%d is least", a);
    }
    
    return 0;
}