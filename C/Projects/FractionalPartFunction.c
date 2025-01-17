#include<stdio.h>
int main(){
    float a;
    printf("Enter a float: ");
    scanf("%f", &a);
    float r;
    int b = a/1;
    r = a-b;
    printf("fractional part is: %f", r);

    return 0;
}