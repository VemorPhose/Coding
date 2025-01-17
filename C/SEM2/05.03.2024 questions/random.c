#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define N 1000

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

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main(){
    int upper = INT_MAX;
    printf("Enter upper bound for randomly generated numbers: ");
    scanf("%d", &upper);
    srand(time(0));

    int A[1000], B[1000], C[1000];
    for(int i = 0; i < N; i++)
        C[i] = B[i] = A[i] = abs(rand()) % upper;

    printf("Original:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n\n\n");

    printf("Quicksorted:\n");
    quicksort(B, 0, N - 1);
    for(int i = 0; i < N; i++)
        printf("%d ", B[i]);
    printf("\n\n\n");

    printf("Insertion sorted:\n");
    insertionSort(C, N);
    for(int i = 0; i < N; i++)
        printf("%d ", C[i]);
    printf("\n\n\n");

    printf("Again enter upper bound: ");
    scanf("%d", &upper);

    for(int i = 0; i < N; i++)
        B[i] = A[i] = abs(rand()) % upper;

    printf("Original:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n\n\n");

    upper >= 1000 ? quicksort(B, 0, N - 1) : insertionSort(B, N);
    printf("Sorted:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", B[i]);
    printf("\n\n\n");

    return 0;
}
