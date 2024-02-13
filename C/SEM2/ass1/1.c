#include <stdio.h>

void f(void); // function declaration

void g(void) { // function declaration and definition
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
return;
}

int main() {
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
f(); // function call
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
int a = 2, b = 3, add(int x, int y);
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
g(); // function call
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
printf("%d + %d = %d\n", a, b, add(a, b)); // function call
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
return; // Will return a garbage value; may cause warning
}

void f() { // function definition
printf("Line: %2d, Function: %s\n", __LINE__, __func__);
g(); // function call
// return; // We may not use it.
}

int add(int a, int b) { // function definition
printf("Line: %d, Function: %s\n", __LINE__, __func__);
return a + b;
}

// %2d fixes width of 2, aligning numbers and trimming extra digits
// __LINE__ returns current line number
// __func__ returns current function name
// blank return within the int function returns 25, possibly pre-existing value in stack
