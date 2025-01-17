#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int partition(int *A, int p, int r){
    int x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        if(A[j] <= x){
            ++i;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    int temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
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
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    printf("enter %d numbers in the array: ");
    int arr[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    quicksort(arr, 0, n-1);
    printf("sorted array is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}