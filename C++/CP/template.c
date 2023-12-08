#include <stdio.h>

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

int armstrongCheck(int n){
    int sum = 0, digits = 0;
    int counter = n;
    while(counter){
        counter /= 10;
        digits++;
    }
    counter = n;
    while(counter){
        int temp = 1, i;
        for(i = 0; i < digits; i++){
            temp *= counter%10;
        }
        counter /= 10;
        sum += temp;
    }
    if(sum == n) return 1;
    else return 0;
}

int numDigits(int n){
    if(n == 0) return 1;
    int digits = 0;
    while(n){
        n /= 10;
        digits++;
    }
    return digits;
}

int lenstr(char s1[]){
    int i = 0;
    while(s1[i] != 0) i++;
    return i;
}

void catstr(char s1[], char s2[]){
    int m = lenstr(s1);
    int n = lenstr(s2);
    int i;
    for(i = 0; i < n; i++){
        s1[i+m] = s2[i];
    }
    s1[m+n] = 0;
}

void cpystr(char s1[], char s2[]){
    int n = lenstr(s2);
    int i;
    for (i = 0; i < n; i++)
    {
        s1[i] = s2[i];
    }
    s1[n] = 0;
}

int cmpstr(char s1[], char s2[]){
    int i = 0;
    int flag = 0;
    while(s1[i] != 0 || s2[i] != 0){
        if(s1[i] < s2[i]){
            flag = -1;
            break;
        }
        if(s1[i] > s2[i]){
            flag = 1;
            break;
        }
    }
    return flag;
}

typedef struct pii{
    int ff;
    int ss;
} pii;

typedef struct psi{
    char ff[100];
    int ss;
} psi;

void bubbleSort(int arr[], int n, int mode){
    int i, j;
    for(i = n-1; i > 0; i--){
        for(j = 0; j < i; j++){
            if(mode == 0 && arr[j] > arr[j+1]){
                arr[j] ^= arr[j+1];
                arr[j+1] ^= arr[j];
                arr[j] ^= arr[j+1];
            }
            else if(mode == 1 && arr[j] < arr[j+1]){
                arr[j] ^= arr[j+1];
                arr[j+1] ^= arr[j];
                arr[j] ^= arr[j+1];
            }
        }
    }
}

int main(){
    int t; scanf("%d", &t);
    while(t--){

    }
    return 0;
}