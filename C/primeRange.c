#include <stdio.h>
#include <math.h>

int isPrime(int n){
    if (n <= 1) return 0;
    int flag = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n%i == 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}

void primeRange(int a, int b){
    int i;
    for(i = a; i <= b; i++){
        if(isPrime(i)) printf("%d\n", i);
    }
}

void main(){
    primeRange(2, 1000000);
}