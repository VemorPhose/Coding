#include <stdio.h>
#include <math.h>
void main()
{
    // printf("give the number of inputs\n");
    int n,l;
    scanf("%i",&n);
    int a[n][2];
    // printf("give size(2^k)(u have to give k), number of squares\n");
    for (int i = 0; i < n; i++) 
        for (int j = 0; j < 2; j++) 
            scanf("%i",&a[i][j]);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j][0] < a[j + 1][0]) {
                int temp = a[j][0];
                a[j][0] = a[j + 1][0];
                a[j + 1][0] = temp;
                temp = a[j][1];
                a[j][1] = a[j + 1][1];
                a[j + 1][1] = temp;
            }
        }
    }
    int op=a[0][0]+1;
    if(round(pow(2,a[0][0]))==2*round(pow(2,a[0][0])))
    if(n>1)
    if(a[0][1]<4*a[1][1])
          op++;
    for (int i = 0; i < n-1; i++) 
    {
          while((round(pow(2,op))/round(pow(2,a[i][0])))*(round(pow(2,op))/round(pow(2,a[i][0])))<a[i][1])
         op++;
    }
    printf("%d",op);
}