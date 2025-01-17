#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubbleSortBestCaseN(int *A, unsigned int n){
    bool swapped = true;
    for(int i = 0; swapped && i < n-1; ++i){
        swapped = false;
        // if no swaps occur --> already sorted --> breaks
        for(int j = 0; j < n-i-1; ++j){
            if(A[j] > A[j+1]){
                swapped = true;
                A[j] ^= A[j+1];
                A[j+1] ^= A[j];
                A[j] ^= A[j+1];
            }
        }
    }
}

int main(){
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    printf("enter %d numbers in the array: "); 
    int arr[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    bubbleSortBestCaseN(arr, n);
    printf("sorted array is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}