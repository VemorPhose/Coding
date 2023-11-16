#include <stdio.h>

void insertionSort(int arr[], int n){
    int i, j;
    for(i = n; i > 0; i--){
        for(j = 0; j < i - 1; j++){
            if(arr[j+1] > arr[j]){
                arr[j+1] ^= arr[j];
                arr[j] ^= arr[j+1];
                arr[j+1] ^= arr[j];
            }
        }
    }
}

void main(){
    int n;
    scanf("%d", &n);
    int arrE[100], countE = 0;
    while(n){
        if(n>=100){
            arrE[countE++] = 100;
            n-=100;
        }
        else if(n>=50){
            arrE[countE++] = 50;
            n-=50;
        }
        else if(n>=20){
            arrE[countE++] = 20;
            n-=20;
        }
        else if(n>=10){
            arrE[countE++] = 10;
            n-=10;
        }
        else if(n>=5){
            arrE[countE++] = 5;
            n-=5;
        }
        else if(n>=2){
            arrE[countE++] = 2;
            n-=2;
        }
        else{
            arrE[countE++] = 1;
            n--;
        }
    }

    int arrB[8][countE];
    int i, j;
    for(i = 0; i < countE; i++){
        for(j = 0; j < 8; j++){
            if(arrE[i]&(1<<(7-j))) arrB[j][i] = 1;
            else arrB[j][i] = 0;
        }
    }

    int arrV[8];
    for(i = 0; i < 8; i++){
        arrV[i] = 0;
        for(j = 0; j < countE; j++){
            if(arrB[i][j]) arrV[i] |= 1<<(countE-1-j);
        }
    }

    insertionSort(arrV, 8);
    for(i = 0; i < 8; i++) if(arrV[i]) printf("%d ", arrV[i]);
}