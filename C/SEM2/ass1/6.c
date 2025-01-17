<<<<<<< HEAD
#include <stdio.h>

void swp(int *p1, int *p2){
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
}

int main(){
    int a = 2, b = 3;
    printf("a = %d, b = %d\n", a, b);
    swp(&a, &b);
    printf("a = %d, b = %d\n", a, b);
}
=======
#include <stdio.h>

void swp(int *p1, int *p2){
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
}

int main(){
    int a = 2, b = 3;
    printf("a = %d, b = %d\n", a, b);
    swp(&a, &b);
    printf("a = %d, b = %d\n", a, b);
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
