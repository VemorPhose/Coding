<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>

void InsSort(int *arr, int n){
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main(){
    int n;
    printf("enter length of array: ");
    scanf("%d", &n);

    int *arr = (int*) calloc(n, sizeof(int));
    printf("enter %d space separated integers: ", n);
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    printf("array before sorting is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    InsSort(arr, n);

    printf("array after sorting is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>

void InsSort(int *arr, int n){
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main(){
    int n;
    printf("enter length of array: ");
    scanf("%d", &n);

    int *arr = (int*) calloc(n, sizeof(int));
    printf("enter %d space separated integers: ", n);
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    printf("array before sorting is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    InsSort(arr, n);

    printf("array after sorting is: ");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
