#include <stdio.h>
#include <stdlib.h>

int main(){
    int size = 0;
    printf("enter size of the array: ");
    scanf("%d", &size);
    int *arr = (int*)malloc(size * sizeof(int));
    printf("enter %d ints\n", size);
    for(int i = 0; i < size; i++){
        scanf("%d", arr+i);
    }
    for(int i = 0; i < size; i++){
        printf("%d ", *(arr+i));
    }
    printf("\n");

    char *c_arr = (char*)arr;
    printf("enter %d chars\n", size * sizeof(int) / sizeof(char));
    for(int i = 0; i < size * sizeof(int) / sizeof(char); i++){
        scanf("%c", c_arr+i);
    }
    for(int i = 0; i < size * sizeof(int) / sizeof(char); i++){
        printf("%c ", *(c_arr+i));
    }
    printf("\n");

    free(arr);
    arr = NULL;
    c_arr = NULL;

    return 0;
}

// chars being inputted are half in number of what it should input
