#include <stdio.h>

// shit aint working

int partition(int *A, int p, int r){
    int x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        if(A[j] <= x){
            ++i;
            A[i+1] ^= A[j];
            A[j] ^= A[i+1];
            A[i+1] ^= A[j];
        }
    }
    A[i+1] ^= A[r];
    A[r] ^= A[i+1];
    A[i+1] ^= A[r];
    return i+1;
}

void quicksort(int *A, int p, int r){
    if(p >= r)
        return;
    int q = partition(A, p, r);
    quicksort(A, p, q-1);
    quicksort(A, q+1, r);
}

int main(){
    int arr[] = {4, 5, 6, 1, 3, 2, 0, 9, 8, 0, 4, 5};
    quicksort(arr, 0, sizeof(arr)/sizeof(int)-1);
    for(int i = 0; i < sizeof(arr)/sizeof(int); i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}