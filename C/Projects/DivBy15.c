#include <stdio.h>
int main()
{
    int a;
    scanf("%d", &a);
    // faulty logic
    /*if (a%5 == 0){
        if (a%3 == 0){
            printf("int is divisible by 15");
        }
    }
    else printf("int is not divisible by 15");*/

    if (a % 5 == 0 && a % 3 == 0 && a != 0)
    {
        printf("int is divisible by 15");
    }

    else
        printf("int is not divisible by 15");

    return 0;
}