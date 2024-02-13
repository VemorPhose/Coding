// strings
#include <stdio.h>

int main(){
    char s[1000];
    // scanf("%[^\n]s", s);
    // fflush(stdin);
    // fflush(stdout);
    scanf("%[^\n]%*c")

    // gets() --> string stored, \n left in stream
    // fgets() --> string + \n both get stored in string
    // %[^\n]s --> string stored, \n left in stream
    // %[^\n]%*c --> string stored, \n discarded

    // fgets --> abc123\n\0
    // %*c --> abc123\0

    s = {'a', 'b', 'c', '\0'};
    s = "abc";
}