#include <stdio.h>
int main()
{
    // for loops
    // for(initialization; condition; updation/incrementation){code}
    // example, code to print seven lines
    for (int i = 1; i <= 7; i++) // i++ is the same as i = i + 1
    {
        printf("dawg\n");
    }

    // while loops
    int j = 1;
    while (j <= 100)
    {
        printf("%d ", j);
        j++;
    }

    // typecasting
    int x = 65;
    char ch = (char)x; //(char) will convert int to corresponding char with same ASCII number.
    printf("\n%c\n", ch);
    int y = (int)ch; //(int) converting the character to corresponding ASCII value.
    printf("%d\n", y);

    return 0;
}