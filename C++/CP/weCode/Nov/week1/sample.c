// decode5. - POORVI AGARWAL.c
#include <stdio.h>
#include <math.h>
int sum();
int main()
{
    int n;
    // printf("enter number : ");
    scanf("%d", &n);
    sum(n);
    return 0;
}

int sum(int n)
{
    int arr[n];
    int i = 0;
    while (n > 0)
    {
        if (n >= 100)
        {
            n = n - 100;
            arr[i] = 100;
            i++;
        }
        else if (n >= 50)
        {
            n = n - 50;
            arr[i] = 50;

            i++;
        }
        else if (n >= 20)
        {
            n = n - 20;
            arr[i] = 20;

            i++;
        }
        else if (n >= 10)
        {
            n = n - 10;
            arr[i] = 10;

            i++;
        }
        else if (n >= 5)
        {
            n = n - 5;
            arr[i] = 5;

            i++;
        }
        else if (n >= 2)
        {
            n = n - 2;
            arr[i] = 2;

            i++;
        }
        else if (n >= 1)
        {
            n = n - 1;
            arr[i] = 1;
            i++;
        }
    }
    int crr[100][8] = {0};

    // for (int j = 0; j < i; j++)
    //     printf("%d ", arr[j]);
    // printf("\n");
    for (int k = 0; k < i; k++)
    {
        for (int j = 7; j >= 0; j--)
        {
            crr[k][j] = arr[k] % 2;

            arr[k] = arr[k] / 2;
        }
    }

    for (int k = 0; k < 8; k++)
    {
        // for (int j = 0; j < i; j++)
        // {
        //     printf("%d ", crr[j][k]);
        // }
        // printf("\n");
    }
    int brr[8];
    int l = 0;
    // printf("binary to decimal form are : ");
    for (int k = 0; k < 8; k++)
    {
        int sum = 0;
        int p = i - 1;
        for (int j = 0; j < i; j++)
        {
            sum = sum + ((pow(2, p)) * crr[j][k]);
            p--;
        }
        brr[l] = sum;
        l++;
    }
    for (int l = 0; l < 8; l++)
    {
        // printf("%d ", brr[l]);
    }
    // printf("\n");
    int temp = 0;
    int num = 0;
    for (int j = 1; j < 8; j++)
    {
        for (int k = 0; k < 8 - j; k++)
        {
            if (brr[k] < brr[k + 1])
            {
                temp = brr[k + 1];
                brr[k + 1] = brr[k];
                brr[k] = temp;
            }
        }
    }
    for (int k = 0; k < 8; k++)
    {
        if (brr[k] != 0)
            num = num * 10 + brr[k];
    }
    printf("%d ", num);

    return 0;
}