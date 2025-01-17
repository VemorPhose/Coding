<<<<<<< HEAD
#include <stdio.h>
int main() {
int a = 4, f(int a);
f(a);
}
int f(int a) {
printf("Line: %2d, a = %d, &a = %p\n", __LINE__, a, &a);
if (a > 0) {
f(a - 1); // recursive call
}
printf("Line: %2d, a = %d, &a = %p\n", __LINE__, a, &a);
return a;
}

// f(int a) within main works as pre-declaration
// rest is simple recursion
=======
#include <stdio.h>
int main() {
int a = 4, f(int a);
f(a);
}
int f(int a) {
printf("Line: %2d, a = %d, &a = %p\n", __LINE__, a, &a);
if (a > 0) {
f(a - 1); // recursive call
}
printf("Line: %2d, a = %d, &a = %p\n", __LINE__, a, &a);
return a;
}

// f(int a) within main works as pre-declaration
// rest is simple recursion
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
