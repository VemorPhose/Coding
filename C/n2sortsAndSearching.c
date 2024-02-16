#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubbleSort(int *A, unsigned int n){
    for(int i = 0; i < n-1; ++i){
        for(int j = 0; j < n-i-1; ++j){
            if(A[j] > A[j+1]){
                A[j] ^= A[j+1];
                A[j+1] ^= A[j];
                A[j] ^= A[j+1];
            }
        }
    }
}

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

int linearSearch(int *A, unsigned int n, int key){
    for(int i = 0; i < n; i++)
        if(A[i] == key)
            return i;
    return -1;
}

int binarySearch(int *A, int lo, int hi, int key){
    if(hi == lo){
        if(A[lo] == key)
            return lo;
        return -1;
    }
    int mid = (lo+hi)/2;
    if(A[mid] >= key)
        return binarySearch(A, lo, mid, key);
    else
        return binarySearch(A, mid+1, hi, key);
}

void printArray(int *A, int n){
    for(int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main(){
    int A[] = {7, 6, 5, 4, 3, 2 ,1};
    int n = sizeof(A)/sizeof(A[0]);
    selectionSort(A, n);
    printArray(A, n);
    printf("%d\n", binarySearch(A, 0, n-1, 6));

    return 0;
}