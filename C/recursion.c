#include <stdio.h>

int factorial(int n){
    if(n==0 || n==1) return 1;
    int out = n * factorial(n-1);
    return out;
}

int sumToN(int n){
    if(n <= 1) return n;
    return n + sumToN(n-1);
}

int fibonacciN(int n){
    if(n==1 || n==2) return 1;
    int out = fibonacciN(n-1) + fibonacciN(n-2);
    return out;
}

int sumDigits(int n){
    int out = n%10 + sumDigits(n/10);
    return out;
}

int sumArr(int arr[], int n){
    
    return out;
}

int main(){

    return 0;
}