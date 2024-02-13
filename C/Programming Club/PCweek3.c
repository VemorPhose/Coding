// Pratapaditya Chander 2301154
#include <stdio.h>
#include <math.h>

//-----------------------GLOBAL VARIABLES--------------------------------

// global array of digits
int arrDigits[9]; // stores sorted array of inital inputted digits
int arrOut[9]; // array after sorting
int arrTemp[9]; // temporary array before sorting

//-----------------------BASIC FUNCTIONS--------------------------------

// prime checker function
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

// number of digits in given int
int digitsNum(int n){
    if(n == 0) return 0;
    return 1 + digitsNum(n/10);
}

// factorial of given int
int factorial(int n){
    if(n <= 1) return 1;
    return n * factorial(n-1);
}

//-----------------------ARRAY MANIPULATION FUNCTIONS--------------------------------

// return int from passed array of digits
int arrToNum(int arrDigits[], int numDigits){
    int num = 0;
    for(int i = 0; i < numDigits; i++){
        num *= 10;
        num += arrDigits[i];
    }
    return num;
}

// converts num to array, stored in arrTemp (global)
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

// compare arrOut (sorted arrTemp) and arrDigits for equality
int arrCmp(int numDigits){
    int flag = 1;
    for(int i = 0; i < numDigits; i++){
        int x = arrOut[i];
        int y = arrDigits[i];
        if(x != y) flag = 0;
    }
    return flag;
}

//-----------------------SORTING FUNCTION--------------------------------

// selection sort descending, from arrTemp (input) to arrOut (output)
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
    // O(numDigits^2)
}

//-----------------------MAIN FUNCTION--------------------------------

void main(){
    // input number of patient
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

    // number of combinations of patient id
    int perms = factorial(numDigits);

    // selection sort descending on array of digits
    selectionSort(numDigits); // arrOut has digits in order of largest number
    arrCpy(arrDigits, arrOut, numDigits); // copied to arrDigits

    // printing basic info lines
    int maxNum = arrToNum(arrDigits, numDigits); // converted array of digits of largest number to int
    printf("The maximum number is: %d\n", maxNum);
    printf("Possible combinations of patient id are: %d\n", perms);

    // for number of digits 1 and 2, least rank i.e. 3 will not be reached.
    if(numDigits < 3){ 
        printf("Not enough combinations to generate required patient id list\n");
    }

    // printing in reverse lexicographical order
    // loop starts from largest number, upto either lowest number of n digits
    // or till required number of ranks are displayed.
    for(int i = maxNum, count = 0; i > (int)pow(10, numDigits-1) && count < perms; i--){
        numToArr(i, numDigits); // arrTemp stores the counter variable digits.
        selectionSort(numDigits); // digits from arrTemp sorted to arrOut.
        if(arrCmp(numDigits)){ // comparing digits of counter number to inputted number
            count++; // increased count of valid numbers.
            if((count%10 == 3 || count%10 == 7) && primeCheck(count)){ // checking for last digit 3, 7 and prime in counter number
                printf("Patient id at rank %d is: %d\n", count, i);
            }
        }
    }
}

//-----------------------FOOTNOTES--------------------------------

// Time complexity: O(10^8 * sqrt(count)) ~~ O(10^10) {worst case}
// Nine and Eight digit numbers take a long while to process.