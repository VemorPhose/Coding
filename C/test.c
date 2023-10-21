#include <stdio.h>
#include <math.h>

int primeCheck(int n){
    if(n <= 1) return 0;
    int upperBound = ceil(sqrt(n)), flag = 1;
    for(int i = 2; i < upperBound; i++){
        if(n % i == 0){
            flag = 0;
            break;
        }
    }
    return flag;
}

int digitsNum(int n){
    if(n == 0) return 0;
    return 1 + digitsNum(n/10);
}

int factorial(int n){
    if(n <= 1) return 1;
    return n * factorial(n-1);
}

// return int from passed array of digits
int numFromArr(int arrDigits[], int numDigits){
    int num = 0;
    for(int i = 0; i < numDigits; i++){
        num *= 10;
        num += arrDigits[i];
    }
    return num;
}

// copy array values to another array.
void arrCpy(int arr1[], int arr2[], int numDigits){
    for(int i = 0; i < numDigits; i++){
        arr2[i] = arr1[i];
    }
}

void main(){
    // data input block
    printf("Total number of patient: ");
    int num;
    scanf("%d", &num);
    if(num <= 0){
        printf("Invalid number!\n");
        return;
    }

    // processing number of digits
    int numDigits = digitsNum(num);

    // separating digits to an array
    int temp = num;
    int arrTemp[numDigits];
    for(int i = 1; i <= numDigits; i++){
        arrTemp[numDigits-i] = temp%10;
        temp /= 10;
    }

    // number of patients
    int perms = factorial(numDigits);

    // selection sort descending on array of digits
    int arrIndex = 0;
    int arrDigits[numDigits];
    for(int i = 0; i < numDigits; i++){
        int maxDigit = 0;
        for(int j = 0; j < numDigits; j++){
            if(arrTemp[j] > maxDigit){
                maxDigit = arrTemp[j];
                arrIndex = j;
            }
        }
        arrTemp[arrIndex] = 0;
        arrDigits[i] = maxDigit;
    }

    // printing basic info lines
    int maxNum = numFromArr(arrDigits, numDigits);
    printf("The maximum number is: %d\n", maxNum);
    printf("Possible combinations of patient id are: %d\n", perms);

    // array of lexicographically arranged numbers
    int arrDict[perms];

}