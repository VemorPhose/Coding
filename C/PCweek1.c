#include <stdio.h>
#include <math.h>

int primeCheck(int n){
    if(n == 1) return 0;
    int counter, flag = 1, upperBound = (sqrt(n) + 1)/1;
    for(counter = 2; counter < upperBound; counter++){
        if(n % counter == 0){
            flag = 0;
            break;
        }
    }
    if(flag == 1) return 1;
    else return 0;
}

int mirror(int n){
    if(n == 1 || n == 3 || n == 8 || n == 0) return n;
    else if(n == 2) return 5;
    else if(n == 5) return 2;
    else return -1;
}

void main(){
    int a, b, numM, numI, counter1, flag4769 = 1, numDigits, counter2;
    printf("enter upper and lower bound a and b: ");
    scanf("%d %d", &a, &b);

    for(counter1 = a; counter1 <= b; counter1++){
        if(primeCheck(counter1)){
            numDigits = 0;
            flag4769 = 1;
            numM = 0;
            numI = 0;
            int num = counter1;            
            while(num){
                numI = numI * 10 + (num % 10);
                if(num % 10 == 4 || num % 10 == 7 || num % 10 == 6 || num % 10 == 9) flag4769 = 0;
                num /= 10;
                numDigits++;
            }
            if(flag4769 == 0) continue;
            num = counter1;
            for(counter2 = numDigits; counter2 > 0; counter2--){
                int tempDigit = (num / (int)pow(10, counter2 - 1));
                numM = numM * 10 + mirror(tempDigit);
                num %= (int)pow(10, counter2 - 1);
            }
            if(primeCheck(numI) && primeCheck(numM)){
                printf("%d\n", counter1);
            }
        }
    }
    // printf("%d", primeCheck(2));
}