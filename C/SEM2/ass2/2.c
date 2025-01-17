#include <stdio.h>
#include <stdlib.h>

int **lowerTriangularMatrix(int n){
    int **ptr = (int**) calloc(n, sizeof(int*));
    int i;
    for(i = 0; i < n; i++){
        ptr[i] = (int*) calloc(i+1, sizeof(int));
    }
    if(ptr != NULL) printf("memory allocated successfully\n");
    else printf("failed to allocate memory\n");
    return ptr;
}

void freeMem2D(int **ptr, int n){
    int i;
    for(i = 0; i < n; i++){
        free(ptr[i]);
    }
    free(ptr);
}

int main(){
    int n;
    printf("enter number of rows in lower triangular matrix: ");
    scanf("%d", &n);
    int **arr = lowerTriangularMatrix(n);

    freeMem2D(arr, n);
    arr = NULL;
    return 0;
}
