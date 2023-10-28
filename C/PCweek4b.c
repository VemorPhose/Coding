// Pratapaditya Chander 2301154
#include <stdio.h>
#include <math.h>

//-------------------------FUNCTION PROTOTYPES-------------------------------

int digitsNum(int n);
int palindromeCheck(int n);
void numToTime(int n, int Time[], int sz);
void printTime(int Time[], int sz);
void backInTime(int n, int Time[], int sz);
void eraseTime(int Time[], int sz);

//---------------------------MAIN FUNCTION-----------------------------------

void main(){
    int n;
    scanf("%d", &n);

    // exception case for n = 0:
    if(n == 0){
        printf("0 (Contents of array Time)\n");
        printf("0 (Nearest Palindromic number less \"than secret number\")\n");
        printf("0 (Time got destroyed)\n");
    }

    // for all other numbers:
    else{
        int sz = (int)floor(log2(n)) + 1;
        int Time[sz];

        // outputting inputted number in binary.
        numToTime(n, Time, sz);
        printTime(Time, sz);
        printf(" (Contents of array Time)\n");

        // finding and outputting greatest base 10
        // palindromic number less than inputted number in binary.
        while(1){
            if(palindromeCheck(n)){
                backInTime(n, Time, sz);
                break;
            }else n--;
        }
        printTime(Time, sz);
        printf(" (Nearest Palindromic number less \"than secret number\")\n");

        // destroying time.
        eraseTime(Time, sz);
        printTime(Time, sz);
        printf(" (Time got destroyed)\n");
    }

    // the end.
    printf("I... Am...... Inevitable.\n");
}

//---------------------------BASIC FUNCTIONS-----------------------------------

// returns number of digits in the given base 10 number.
int digitsNum(int n){
    if(n == 0) return 0;
    return 1 + digitsNum(n/10);
}

// checks if the given base 10 number is a palindrome.
int palindromeCheck(int n){
    int numDigits = digitsNum(n);
    if(numDigits == 1 || numDigits == 0) return 1;
    int space[numDigits], i;
    
    for(i = numDigits-1; i >= 0; i--){
        space[i] = n%10;
        n /= 10;
    }

    int flag = 1;
    for(i = 0; i < numDigits/2; i++){
        if(space[i] != space[numDigits-1-i]){
            flag = 0;
            break;
        }
    }
    return flag;
}

//---------------------------ARRAY MANIPULATION FUNCTIONS-----------------------------------

// converts given base 10 number to binary and stores in Time[] while iterating forward.
void numToTime(int n, int Time[], int sz){
    int i, temp;
    for(i = 0; i < sz; i++){
        temp = pow(2, sz-1-i);
        if(n >= temp){
            Time[i] = 1;
            n -= temp;
        }
        else{
            Time[i] = 0;
        }
    }
}

// prints the binary number stored in Time[].
void printTime(int Time[], int sz){
    int i;
    for(i = 0; i < sz; i++){
        printf("%d", Time[i]);
    }
}

// iterates Time[] in reverse and updates it to the binary equivalent of 
// greatest base 10 palindromic number less than given number.
void backInTime(int n, int Time[], int sz){
    int i, temp;
    for(i = sz-1; i >= 0; i--){
        temp = n%2;
        if(Time[i] != temp){
            if(Time[i] == 1) Time[i] = 0;
            else Time[i] = 1;
        }
        n /= 2;
    }
}

// updates all elements in Time[] to 0.
void eraseTime(int Time[], int sz){
    int i;
    for(i = 0; i < sz; i++){
        Time[i] = 0;
    }
}

//--------------------------------THE END----------------------------------------