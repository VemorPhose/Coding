#include <stdio.h>
#include <math.h>
#define PI 3.14159265

int primeCheck(int n){
    if(n <= 1) return 0;
    int counter, flag = 1;
    for(counter = 2; counter < n; counter++){
        if(n%counter == 0){
            flag = 0;
            break;
        }
    }
    return flag;
}

void primeRange(int a, int b){
    int counter;
    for(counter = a; counter <= b; counter++){
        if(primeCheck(counter)) printf("%d\n", counter);
    }
}

float areaCircle(float diam){
    return PI * (diam/2.0) * (diam/2.0);
}

int armstrongCheck(int n){
    int sum = 0, digits = 0;
    int counter = n;
    while(counter){
        counter /= 10;
        digits++;
    }
    counter = n;
    while(counter){
        int temp = 1, i;
        for(i = 0; i < digits; i++){
            temp *= counter%10;
        }
        counter /= 10;
        sum += temp;
    }
    if(sum == n) return 1;
    else return 0;
}

void armstrongRange(int a, int b){
    int i;
    for(i = a; i <= b; i++){
        if(armstrongCheck(i)){
            printf("%d\n", i);
        }
    }
}

int max3(int a, int b, int c){
    if(a > b){
        if(c > a) return c;
        else return a;
    }
    else{
        if(c > b) return c;
        else return b;
    }
}

int digitsNum(int n){
    if(n == 0) return 1;
    int digits = 0;
    while(n){
        n /= 10;
        digits++;
    }
    return digits;
}

void main(){
    printf("Hello World!\n");
}