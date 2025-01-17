#include <stdio.h>
#include <stdlib.h>
int x = 1, y;
static int a = 2, b;
void f(){}
static void g();
int main(int argc, char *argv[]) {
static int u = 3, v;
int s = 4, t;
printf("CODE/TEXT SEGMENT (LOW MEMORY):\n");
printf("f = %p\n", f);
printf("main = %p\n", main);
printf("g = %p\n", g);
printf("printf = %p (library function)\n", printf);
printf("\n");
printf("DATA SEGMENT (INITIALIZED):\n");
printf("x = %d, &x = %p (external) \n", x, &x);
printf("a = %d, &a = %p (static) \n", a, &a);
printf("u = %d, &u = %p (static, local to main)\n", u, &u);
printf("\n");
printf("DATA SEGMENT (UNINITIALIZED):\n");
printf("y = %d, &y = %p (external)\n", y, &y);
printf("b = %d, &b = %p (static)\n", b, &b);
printf("v = %d, &v = %p (static, local to main)\n", v, &v);
printf("\n");
printf("HEAP:\n");
printf("address = %p\n", calloc(1, 1));
printf("\n");

printf("STACK SEGMENT (INITIALIZED/UNINITIALIZED):\n");
printf("s = %d, &s = %p\n", s, &s);
printf("t = %d, &t = %p\n", t, &t);
g();
printf("\n");
printf(
"+-------------------------+\n"
"| STACK | (HIGH MEMORY)\n"
"+-------------------------+\n"
"| | |\n"
"| V |\n"
"| |\n"
"| |\n"
"| ^ |\n"
"| | |\n"
"+-------------------------+\n"
"| HEAP |\n"
"+-------------------------+\n"
"| UNINITIALIZED DATA (BSS)|\n"
"+-------------------------+\n"
"| INITIALIZED DATA (DATA) |\n"
"+-------------------------+\n"
"| TEXT/CODE SEGMENT | (LOW MEMORY)\n"
"+-------------------------+\n\n"
);
printf("Block Starting Symbol (BSS) portion contains "
"statically-allocated variables."
);
return 0;
}
static void g(){
int i = 1;
printf("i = %d, &i = %p (stack grows)\n", i, &i);
}

// outputs are addresses of various objects stored at different locations of memory
// code/text segment stores function names, library function names, etc
// data segment initialized and uninitialized, store global variables,
// static variables, extern variables.
// while stack memory segment stores auto variables within functions.
// heap memory stores dynamically allocated variables
