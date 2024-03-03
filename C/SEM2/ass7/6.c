#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void selectionSort(int *A, unsigned int n){
    int index = 0;
    for(int i = 0; i < n-1; i++){
        index = i;
        for(int j = i+1; j < n; j++){
            if(A[j] < A[index])
                index = j;
        }
        if(i != index){
            A[i] ^= A[index];
            A[index] ^= A[i];
            A[i] ^= A[index];
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
    selectionSort(arr, n);
    printf("sorted array is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}