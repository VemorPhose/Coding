#include <stdio.h>
#include <stdlib.h>

int **matrix(int m, int n){
    int **ptr = (int**) malloc(m* sizeof(int*));
    int i;
    for(i = 0; i < m; i++){
        ptr[i] = (int*) malloc(n* sizeof(int));
    }
    if(ptr != NULL) printf("memory allocated successfully\n");
    else printf("failed to allocate memory\n");
    return ptr;
}

int **matrixMult(int **mat1, int **mat2, int m, int n, int p){
    int **mattress = matrix(m, p);
    int i, j, k;
    for(i = 0; i < m; i++){
        for(j = 0; j < p; j++){
            mattress[i][j] = 0;
            for(k = 0; k < n; k++){
                mattress[i][j] += (mat1[i][k] * mat2[k][j]);
            }
        }
    }
    return mattress;
}

void freeMem2D(int **ptr, int n){
    int i;
    for(i = 0; i < n; i++){
        free(ptr[i]);
    }
    free(ptr);
}

int main(){
    int m, n, p;
    printf("enter m, n, p: ");
    scanf("%d %4d %d", &m, &n, &p);
    int **arr = matrix(m, n);
    int **brr = matrix(n, p);
    printf("enter %d x %d matrix 1: \n", m, n);
    int i, j;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            scanf("%d", &arr[i][j]);
        }
    }
    printf("enter %d x %d matrix 2: \n", n, p);
    for(i = 0; i < n; i++){
        for(j = 0; j < p; j++){
            scanf("%d", &brr[i][j]);
        }
    }

    int **mattress = matrixMult(arr, brr, m, n, p);
    for(i = 0; i < m; i++){
        for(j = 0; j < p; j++){
            printf("%d ", mattress[i][j]);
        }
        printf("\n");
    }

    freeMem2D(arr, m);
    arr = NULL;
    freeMem2D(brr, n);
    brr = NULL;
    freeMem2D(mattress, m);
    mattress = NULL;
    return 0;
}
