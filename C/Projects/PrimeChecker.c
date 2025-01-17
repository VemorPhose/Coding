#include<stdio.h>
int main(){
    int x;
    int counter = 1;
    printf("enter an int: ");
    scanf("%d", &x);

    for (int i = 2; i < x; i = i + 1)
    {
        if (x % i == 0)
        {
            counter = 0;
            break;
        }
    }
    
    counter == 0 ? printf("not a prime") : printf("prime");
    
    return 0;
}