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

// global array of digits
int arrDigits[9];
int arrOut[9];
int arrTemp[9];

// return int from passed array of digits
int arrToNum(int arrDigits[], int numDigits){
    int num = 0;
    for(int i = 0; i < numDigits; i++){
        num *= 10;
        num += arrDigits[i];
    }
    return num;
}

// converts num to array, stored in arrOut (global)
void numToArr(int num, int numDigits){
    for(int i = numDigits-1; i >= 0; i--){
        arrTemp[i] = num % 10;
        num /= 10;
    }
}

// copy array values to another array.
void arrCpy(int arr2[], int arr1[], int numDigits){
    for(int i = 0; i < numDigits; i++){
        arr2[i] = arr1[i];
    }
}

// compare arrays as equal or not
int arrCmp(int numDigits){
    int flag = 1;
    for(int i = 0; i < numDigits; i++){
        int x = arrOut[i];
        int y = arrDigits[i];
        if(x != y) flag = 0;
    }
    return flag;
}

// selection sort
void selectionSort(int numDigits){
    int arrIndex = 0;
    for(int i = 0; i < numDigits; i++){
        int maxDigit = 0;
        for(int j = 0; j < numDigits; j++){
            if(arrTemp[j] > maxDigit){
                maxDigit = arrTemp[j];
                arrIndex = j;
            }
        }
        arrTemp[arrIndex] = 0;
        arrOut[i] = maxDigit;
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
    for(int i = 1; i <= numDigits; i++){
        arrTemp[numDigits-i] = temp%10;
        temp /= 10;
    }

    // number of patients
    int perms = factorial(numDigits);

    // selection sort descending on array of digits
    selectionSort(numDigits);
    arrCpy(arrDigits, arrOut, numDigits);

    // printing basic info lines
    int maxNum = arrToNum(arrDigits, numDigits);
    printf("The maximum number is: %d\n", maxNum);
    printf("Possible combinations of patient id are: %d\n", perms);

    // printing in reverse lexicographical order
    for(int i = (int)pow(10, numDigits), count = 0; i > (int)pow(10, numDigits-1) && count < perms; i--){
        numToArr(i, numDigits);
        selectionSort(numDigits);
        if(arrCmp(numDigits)){
            count++;
            if((count%10 == 3 || count%10 == 7) && primeCheck(count)){
                printf("Patient id at rank %d is: %d\n", count, i);
            }
        }
    }
}