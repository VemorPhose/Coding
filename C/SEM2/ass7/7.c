<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *A, int lo, int hi){
    if(lo >= hi)
        return;
    int mid = (lo+hi)/2;
    mergeSort(A, lo, mid);
    mergeSort(A, mid+1, hi);
    merge(A, lo, mid, hi);
    return;
}

int main(){
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    printf("enter %d numbers in the array: ", n);
    int arr[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    mergeSort(arr, 0, n-1);
    printf("sorted array is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int *A, int lo, int hi){
    if(lo >= hi)
        return;
    int mid = (lo+hi)/2;
    mergeSort(A, lo, mid);
    mergeSort(A, mid+1, hi);
    merge(A, lo, mid, hi);
    return;
}

int main(){
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    printf("enter %d numbers in the array: ", n);
    int arr[n];
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    mergeSort(arr, 0, n-1);
    printf("sorted array is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
