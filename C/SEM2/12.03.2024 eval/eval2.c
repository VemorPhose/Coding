<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define N 50

int partition(int *A, int p, int r, int *cntA, int *cntB){
    int x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        *cntA+=1;
        if(A[j] <= x){
            ++i;
            *cntB += 1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    *cntB += 1;
    int temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
    return i+1;
}

void quicksort(int *A, int p, int r, int *cntA, int *cntB){
    if(p >= r)
        return;
    int q = partition(A, p, r, cntA, cntB);
    quicksort(A, p, q-1, cntA, cntB);
    quicksort(A, q+1, r, cntA, cntB);
}

void bubbleSortBestCaseN(int *A, unsigned int n, int *cntA, int *cntB){
    bool swapped = true;
    for(int i = 0; swapped && i < n-1; ++i){
        swapped = false;
        // if no swaps occur --> already sorted --> breaks
        for(int j = 0; j < n-i-1; ++j){
            *cntA += 1;
            if(A[j] > A[j+1]){
                *cntB += 1;
                swapped = true;
                A[j] ^= A[j+1];
                A[j+1] ^= A[j];
                A[j] ^= A[j+1];
            }
        }
    }
}


int main(){
    int upper = INT_MAX, lower = INT_MIN;
    printf("Enter lower and upper bound for randomly generated numbers: ");
    scanf("%d %d", &lower, &upper);
    srand(time(0));

    int A[N], B[N], C[N];
    for(int i = 0; i < N; i++)
        C[i] = B[i] = A[i] = lower + abs(rand()) % (upper - lower);

    printf("Original:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n\n\n");

    int cntBa = 0, cntBb = 0;
    bubbleSortBestCaseN(B, N, &cntBa, &cntBb);
    printf("Bubble sorted:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", B[i]);
    printf("\nno. of swaps: %d, no. of comparisons: %d\n", cntBb, cntBa);
    printf("\n\n\n");

    int cntCa = 0, cntCb = 0;
    quicksort(C, 0, N - 1, &cntCa, &cntCb);
    printf("Quicksorted:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", C[i]);
    printf("\nno. of swaps: %d, no. of comparisons: %d\n", cntCb, cntCa);
    printf("\n\n\n");

    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define N 50

int partition(int *A, int p, int r, int *cntA, int *cntB){
    int x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        *cntA+=1;
        if(A[j] <= x){
            ++i;
            *cntB += 1;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    *cntB += 1;
    int temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
    return i+1;
}

void quicksort(int *A, int p, int r, int *cntA, int *cntB){
    if(p >= r)
        return;
    int q = partition(A, p, r, cntA, cntB);
    quicksort(A, p, q-1, cntA, cntB);
    quicksort(A, q+1, r, cntA, cntB);
}

void bubbleSortBestCaseN(int *A, unsigned int n, int *cntA, int *cntB){
    bool swapped = true;
    for(int i = 0; swapped && i < n-1; ++i){
        swapped = false;
        // if no swaps occur --> already sorted --> breaks
        for(int j = 0; j < n-i-1; ++j){
            *cntA += 1;
            if(A[j] > A[j+1]){
                *cntB += 1;
                swapped = true;
                A[j] ^= A[j+1];
                A[j+1] ^= A[j];
                A[j] ^= A[j+1];
            }
        }
    }
}


int main(){
    int upper = INT_MAX, lower = INT_MIN;
    printf("Enter lower and upper bound for randomly generated numbers: ");
    scanf("%d %d", &lower, &upper);
    srand(time(0));

    int A[N], B[N], C[N];
    for(int i = 0; i < N; i++)
        C[i] = B[i] = A[i] = lower + abs(rand()) % (upper - lower);

    printf("Original:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n\n\n");

    int cntBa = 0, cntBb = 0;
    bubbleSortBestCaseN(B, N, &cntBa, &cntBb);
    printf("Bubble sorted:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", B[i]);
    printf("\nno. of swaps: %d, no. of comparisons: %d\n", cntBb, cntBa);
    printf("\n\n\n");

    int cntCa = 0, cntCb = 0;
    quicksort(C, 0, N - 1, &cntCa, &cntCb);
    printf("Quicksorted:\n");
    for(int i = 0; i < N; i++)
        printf("%d ", C[i]);
    printf("\nno. of swaps: %d, no. of comparisons: %d\n", cntCb, cntCa);
    printf("\n\n\n");

    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
