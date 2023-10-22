#include <stdio.h>
#include <math.h>

int fact(int);
int prime(int someNum);
int numberGenerator(int, int, int);
int digitCounter(int);


int main(){
    // Taking input
    int input=987654321;
    printf("Total number of patient:");
    scanf("%d", &input);

    // Making an array with all the digits
    int digit = digitCounter(input), in = input;
    int digits[digit];
    in = input;
    for (int _ = 0; _ < digit; _++){
        digits[_] = (in%10);
        in/=10;
    }

    // Sorting the array
    for (int _ = 0; _ < digit; _++){
        for (int _2 = _+1; _2 < digit; _2++){
            if (digits[_] > digits[_2]) {
                int temp = digits[_];
                digits[_] = digits[_2];
                digits[_2] = temp;
            }
        }
    }

    // converting sorted array into integer to be able to pass it to functions (points not yet taught, it's complicated)
    int sortedNumber = 0;
    for (int _ = 0; _ < digit; _++){
        sortedNumber*=10;
        sortedNumber+= digits[_];
    }

    // Finding and printing results
    int maxCases = fact(digit);
    printf("Possible combinations of patient IDs: %d\n", maxCases);

//    for (int _ = 0; _ < maxCases; _++) {
//        if (((_ % 10 == 3) || (_ % 10 == 7)) && (prime(_))) {
//            printf("Patient ID at rank %d is: \t%d\n", _, numberGenerator(_, sortedNumber, digit));
//        }
//    }

    numberGenerator(13, sortedNumber, digit);
}


// why list all the numbers when we can calculate the number at n-th position
int numberGenerator(int rank, int number, int numberOfDigits) {
    // Was more comfortable in finding the rank from lowest to highest
    // so simply converted the descending rank to ascending rank
    // rank = fact(numberOfDigits) - rank;

    int resultant = 0;
    rank--;
    int prevFact = 1;
    printf("%d\n", rank);
    for (int _ = 0; _ < numberOfDigits -1; _++) {
        int index = ((rank%prevFact) / fact(digitCounter(number) -1));
        prevFact = fact(digitCounter(number) - 1);
        int digitAtIndex = (number/ (int) pow(10, digitCounter(number) - index - 1)) % 10;
        resultant*=10;
        resultant+=digitAtIndex;
        number = ((number/(int)pow(10, digitCounter(number) - index)) * (int)pow(10, digitCounter(number) - index - 1) + number%(int)pow(10, digitCounter(number) - index -1));
        printf("%d\t%d\t%d\n", number, index, resultant);
    }
    resultant*=10;
    resultant+=number;
    printf("%d", resultant);
    return resultant;
}

int digitCounter(int input){
    int digit=0;
    while (input){
        digit++;
        input/=10;
    }
    return digit;
}

int fact(int _) {
    int out = 1;
    while (_) {
        out*=_;
        _--;
    }
    return out;
}

int prime(int someNum) {
    int sqrt_i = sqrt(someNum);
    for (int _=2; _<=sqrt_i; _++){
        if (!(someNum%_)){
            return 0;
        }
    }
    return 1;
}