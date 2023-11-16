#include <stdio.h>
void func(int* a, int* b){
    printf("%d\n", *a + *b);
}

void printArr(int* arr, int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

void main(){
    int a = 5;
    int b = 3;

    func(&a, &b);

    int n = 10;
    int arr[n];
    int i;
    for(i = 0; i < 10; i++){
        scanf("%d", &arr[i]);
    }
    printArr(arr, n);
}