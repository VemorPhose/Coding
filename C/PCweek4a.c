// Pratapaditya Chander 2301154
#include <stdio.h>

void main(){
    int n;
    scanf("%d", &n);
    long long int sumToN = (n * (n+1))/2; // sum of all numbers to n.
    
    int i, temp;
    for(i = 0; i < n - 1; i++){
        scanf("%d", &temp);
        sumToN -= temp; // each step subtracts the inputted number from sum.
    }
    // the resultant number is the only number not subtracted from sum of all numbers, i.e. the missing number.
    printf("%d", sumToN);
}