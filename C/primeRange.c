#include <stdio.h>
#include <math.h>

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

void main(){
    primeRange(2, 1000000);
}