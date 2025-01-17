#include <stdio.h>

// 1b
int factorial(int n)
{
if(n==0||n==1) return 1;
if(n < 0) return 0;
int i, returnee = 1;
for(i = n; i > 1; i--) returnee *= i;
return returnee;
}


// 1e
int isPrime(int n){
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

void main()
{
int n;
printf("enter n: ");
scanf("%d", &n);

// 1a
// creating array of digits
int i, j, arr[10];
int temp = n;
while(temp)
{
arr[i] = temp%10;
temp /= 10;
i++;
}
// for(j = 0; j < i; j++) printf("%d ", arr[j]);
// printf("\n");

// separating to arrays of odd and even place digits
int oddArr[5], evenArr[5];
int oddIndex = 0, evenIndex = 0;
for(j = 0; j < i; j++)
{
if(j%2==0)
{
oddArr[oddIndex] = arr[j];
oddIndex++;
}
else
{
evenArr[evenIndex] = arr[j];
evenIndex++;
}
}

// outputting digits at odd and even places
printf("Digits at odd places of n are: \n");
for(i = oddIndex-1; i >= 0; i--) printf("%d ", oddArr[i]);
printf("\n");
printf("Digits at even places of n are: \n");
for(i = evenIndex-1; i >= 0; i--) printf("%d ", evenArr[i]);
printf("\n\n");

// 1b
int sumFact = 0;
for(i = 0; i < evenIndex; i++) sumFact += factorial(evenArr[i]);
printf("Sum of factorial of digits at even places: %d\n\n", sumFact);

// 1c
int m = 0;
for(i = oddIndex-1; i >= 0; i--)
{
m *= 10;
m += oddArr[i];
}
printf("Number formed with digits at odd places (m): %d\n\n", m);

// 1d
printf("Factors of %d: ", m);
for(i = 1; i <= m; i++) if(m%i==0) printf("%d ", i);
printf("\n\n");

// 1e
printf("Prime-Factors of %d: ", m);
for(i = 1; i <= m; i++) if(m%i==0) if(isPrime(i)) printf("%d ", i);
printf("\n");
printf("Non Prime-Factors: ");
for(i = 1; i <= m; i++) if(m%i==0) if(!isPrime(i)) printf("%d ", i);
printf("\n\n");
}