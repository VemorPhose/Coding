#include <stdio.h>
int x; // can be accessed from outside this file by declaring it using extern
static int y; // access restricted to this file
void f() { // can be accessed from outside this file
static int count; // accessible only to this function; default value is 0
count++;

printf("%s is called %d time(s).\n", __func__, count);
return;
}
static void g() { // access restricted to this file
printf("Inside %s\n", __func__);
}
void main(void) {
void f();
printf("x = %d, y = %d\n", x, y); // default value is 0
f();
f();
f();
}

// x and y are global variables, default values are thus 0.
// count is static and thus value is persistent through each function call
// understand use cases of static and extern
