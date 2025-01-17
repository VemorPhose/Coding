#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>>


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

int partitionchar(char *A, int p, int r){
    char x = A[r];
    int i = p-1;
    for(int j = p; j < r; j++){
        if(A[j] <= x){
            ++i;
            char temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    char temp = A[i+1];
    A[i+1] = A[r];
    A[r] = temp;
    return i+1;
}

void quicksortchar(char *A, int p, int r){
    if(p >= r)
        return;
    int q = partitionchar(A, p, r);
    quicksortchar(A, p, q-1);
    quicksortchar(A, q+1, r);
}

int main(){
    int n;
    printf("enter size of S: ");
    scanf("%d", &n);
    char A[n+1];
    printf("enter S: ");
    scanf("%s", A);
    int i = 0, c = 0;
    int I[n];
    char C[n];
    int flag = 0;
    for(int k = 0; k < n; k++){
        if(A[k] == 0)
            continue;
        if(flag){
            I[i] = -1 * (int)(A[k] - '0');
            i++;
            flag = 0;
            continue;
        }
        if(A[k] == '-'){
            flag = 1;
            continue;
        }
        if(A[k] >= '0' && A[k] <= '9'){
            I[i] = (int)(A[k] - '0');
            i++;
        }
        else{
            C[c] = A[k];
            c++;
        }
    }

    for(int k = 0; k < i; k++)
        printf("%d ", I[k]);
    for(int k = 0; k < c; k++)
        printf("%c ", C[k]);
    printf("\n\n");

    for(int k = 0; k < c; k++)
        printf("%c ", C[k]);
    for(int k = 0; k < i; k++)
        printf("%d ", I[k]);
    printf("\n\n");

    bubbleSortBestCaseN(I, i);
    quicksortchar(C, 0, c-1);

    for(int k = 0; k < i; k++)
        printf("%d ", I[k]);
    for(int k = 0; k < c; k++)
        printf("%c ", C[k]);
    printf("\n\n");

    for(int k = 0; k < c; k++)
        printf("%c ", C[k]);
    for(int k = 0; k < i; k++)
        printf("%d ", I[k]);
    printf("\n\n");

    return 0;
}
