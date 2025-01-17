<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>

int *findMinMax(int *arr, int n){
    int M = 0, m = 0;
    int i;
    for(i = 0; i < n; i++){
        if(arr[i] < arr[m]) m = i;
        if(arr[i] > arr[M]) M = i;
    }
    int *ret = (int*) calloc(2, sizeof(int));
    ret[0] = m; ret[1] = M;
    return ret;
}

void swapMinMax(int *arr, int n){
    int *mM = findMinMax(arr, n);
    arr[mM[0]] ^= arr[mM[1]];
    arr[mM[1]] ^= arr[mM[0]];
    arr[mM[0]] ^= arr[mM[1]];
    free(mM);
    mM = NULL;
}

int sum(int *arr, int n){
    int ret = 0;
    int i;
    for(int i = 0; i < n; i++) ret += arr[i];
    return ret;
}

float avg(int *arr, int n){
    float ret = (float)sum(arr, n);
    ret/=n;
    return ret;
}

int findarr(int *arr, int n, int f){
    int i;
    for(i = 0; i < n; i++) if(arr[i] == f) return i;
    return -1;
}

int main(){
    int n;
    printf("enter size of array: ");
    scanf("%d", &n);
    int *arr = (int*) calloc(n, sizeof(int));
    int i;
    printf("enter %d numbers: ", n);
    for(i = 0; i < n; i++) scanf("%d", arr+i);
    // 1
    for(i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    // 2
    int *mM = findMinMax(arr, n);
    printf("indices of minimum and maximum valued elements are %d and %d\n", mM[0], mM[1]);
    // 3
    swapMinMax(arr, n);
    mM = findMinMax(arr, n);
    printf("indices of minimum and maximum valued elements after swap are %d and %d\n", mM[0], mM[1]);
    // 4
    printf("sum of all elements of the array is %d\n", sum(arr, n));
    // 5
    printf("avg of all elements of the array is %f\n", avg(arr, n));
    // 6
    int f;
    printf("enter a value to find: ");
    scanf("%d", &f);
    int ind = findarr(arr, n, f);
    if(ind < 0) printf("element not found\n");
    else printf("index of the element is %d\n", ind);
    // 7
    printf("address of each element in the array is:\n");
    for(i = 0; i < n; i++){
        printf("%p ", arr+i);
    }
    printf("\n");

    free(arr);
    arr = NULL;
    free(mM);
    mM = NULL;
    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>

int *findMinMax(int *arr, int n){
    int M = 0, m = 0;
    int i;
    for(i = 0; i < n; i++){
        if(arr[i] < arr[m]) m = i;
        if(arr[i] > arr[M]) M = i;
    }
    int *ret = (int*) calloc(2, sizeof(int));
    ret[0] = m; ret[1] = M;
    return ret;
}

void swapMinMax(int *arr, int n){
    int *mM = findMinMax(arr, n);
    arr[mM[0]] ^= arr[mM[1]];
    arr[mM[1]] ^= arr[mM[0]];
    arr[mM[0]] ^= arr[mM[1]];
    free(mM);
    mM = NULL;
}

int sum(int *arr, int n){
    int ret = 0;
    int i;
    for(int i = 0; i < n; i++) ret += arr[i];
    return ret;
}

float avg(int *arr, int n){
    float ret = (float)sum(arr, n);
    ret/=n;
    return ret;
}

int findarr(int *arr, int n, int f){
    int i;
    for(i = 0; i < n; i++) if(arr[i] == f) return i;
    return -1;
}

int main(){
    int n;
    printf("enter size of array: ");
    scanf("%d", &n);
    int *arr = (int*) calloc(n, sizeof(int));
    int i;
    printf("enter %d numbers: ", n);
    for(i = 0; i < n; i++) scanf("%d", arr+i);
    // 1
    for(i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    // 2
    int *mM = findMinMax(arr, n);
    printf("indices of minimum and maximum valued elements are %d and %d\n", mM[0], mM[1]);
    // 3
    swapMinMax(arr, n);
    mM = findMinMax(arr, n);
    printf("indices of minimum and maximum valued elements after swap are %d and %d\n", mM[0], mM[1]);
    // 4
    printf("sum of all elements of the array is %d\n", sum(arr, n));
    // 5
    printf("avg of all elements of the array is %f\n", avg(arr, n));
    // 6
    int f;
    printf("enter a value to find: ");
    scanf("%d", &f);
    int ind = findarr(arr, n, f);
    if(ind < 0) printf("element not found\n");
    else printf("index of the element is %d\n", ind);
    // 7
    printf("address of each element in the array is:\n");
    for(i = 0; i < n; i++){
        printf("%p ", arr+i);
    }
    printf("\n");

    free(arr);
    arr = NULL;
    free(mM);
    mM = NULL;
    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
