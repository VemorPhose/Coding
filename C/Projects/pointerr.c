#include<stdio.h>
int swapbyvalue(int a,int b){
    int temp = a;
    a = b;
    b = temp;
}
int swapbyreference(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main(){
    int a = 2;
    int b = 5;
    swapbyvalue(a,b);
    printf("a is %d and b is %d\n", a, b);

    swapbyreference(&a, &b);
    printf("a is %d and b is %d\n", a, b);

    return 0;
}