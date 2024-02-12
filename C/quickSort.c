#include <stdio.h>
#include <stdlib.h>

void quicksort(int *A, int p, int r){
    int q = partition(A, p, r);
    quicksort(A, p, q-1);
    quicksort(A, q+1, r);
}

int partition(int *A, int p, int r){
    int x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        if(A[j] <= x){
            ++i;
            A[i+1] ^= A[r];
            A[r] ^= A[i+1];
            A[i+1] ^= A[r];
        }
    }
    A[i+1] ^= A[r];
    A[r] ^= A[i+1];
    A[i+1] ^= A[r];
    return i+1;
}