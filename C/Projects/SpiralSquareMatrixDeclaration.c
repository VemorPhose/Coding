#include <stdio.h>
#include <stdbool.h>
int main()
{
    printf("rows: ");
    int r;
    scanf("%d", &r);
    printf("columns: ");
    int c;
    scanf("%d", &c);
    int arr[r][c];
    int r_end = r / 2, c_end;
    if (c % 2 == 1)
        c_end = c / 2;
    else
        c_end = c / 2 - 1;

    int rf = r - 1, cf = c - 1, rs = 0, cs = 0, counter = 1;

    while (true)
    {
        for (int i = cs; i <= cf; i++)
        {
            arr[rs][i] = counter++;
        }
        rs++;
        if (cf == c_end && rf == r_end) break;
        for (int i = rs; i <= rf; i++)
        {
            arr[i][cf] = counter++;
        }
        cf--;
        for (int i = cf; i >= cs; i--)
        {
            arr[rf][i] = counter++;
        }
        if (cs == c_end && rf == r_end) break;
        rf--;
        for (int i = rf; i >= rs; i--)
        {
            arr[i][cs] = counter++;
        }
        cs++;
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
    
}