<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

int main (){
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    int arr[n];
    printf("enter first descending then ascending array of n elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int ind = 0;
    for (int i = 1; i < n; i++){
        if (arr[i] > arr[i-1]){
            ind = i-1;
            break;
        }
    }
    if (ind == 0 && arr[1] < arr[0])
        ind = n-1;

    int p = ind, q = ind+1;
    int k = 0;
    int brr[n];
    for (; k < n; k++){
        if (p == -1)
            brr[k] = arr[q++];
        else if (q == n)
            brr[k] = arr[p--];
        else if (arr[p] > arr[q])
            brr[k] = arr[q++];
        else brr[k] = arr[p--];
    }

    for (int i = 0; i < n; i++)
        printf("%d ", brr[i]);
    printf("\n");

    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

int main (){
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    int arr[n];
    printf("enter first descending then ascending array of n elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int ind = 0;
    for (int i = 1; i < n; i++){
        if (arr[i] > arr[i-1]){
            ind = i-1;
            break;
        }
    }
    if (ind == 0 && arr[1] < arr[0])
        ind = n-1;

    int p = ind, q = ind+1;
    int k = 0;
    int brr[n];
    for (; k < n; k++){
        if (p == -1)
            brr[k] = arr[q++];
        else if (q == n)
            brr[k] = arr[p--];
        else if (arr[p] > arr[q])
            brr[k] = arr[q++];
        else brr[k] = arr[p--];
    }

    for (int i = 0; i < n; i++)
        printf("%d ", brr[i]);
    printf("\n");

    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
