#include <stdio.h>
#include <math.h>

int numOfCoins(int n, int coins[7]);
int binarize(int n, int binCoin[8]);
void sort(int arr[8]);

int main(void)
{
    int n;
    printf("Enter value in Earth currency: ");
    scanf("%d", &n);

    if (n > pow(2,8) || n < 1)
    {
        printf("INVALID INPUT!\n");
        return 1;
    }

    int coins[7], binCoin[8], binCoins[8][7];

    int c = numOfCoins(n, coins);
    printf("Processing Steps:\n");

    for(int i = 0; i < c; i++)
        printf("%4d", coins[i]);

    printf("\n");
    
    for (int i = 0; i < c; i++)
    {
        binarize(coins[i], binCoin);

        for (int j = 0; j < 8; j++)
        {
            binCoins[j][i] = binCoin[7 - j];
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0;  j < c; j++)
        {
            printf ("%4d", binCoins[i][j]);
        }
        printf ("\n");
    }
    
    int vCoins[8] = {0};
    for (int i = 0; i < 8; i++)
    {
        vCoins[i] = binCoins[i][0] * 4 + binCoins[i][1] * 2 + binCoins[i][2] * 1;
        printf("%d ", vCoins[i]);
    }
    
    sort(vCoins);
    printf("\n");
    
    int i;
    
    while(vCoins[i])
        printf("%d ", vCoins[i++]);
}

int numOfCoins(int n, int coin[7])
{
    int earthCoins[7] = {100, 50, 20, 10, 5, 2, 1};
    int j = 0;
    for (int i = 0; i < 7; i++)
    {
        if (n >= earthCoins[i])
        {
            coin[j] = earthCoins[i];
            n -= earthCoins[i];
            j++;
        }
        if (n == 0)
            break;
    }
    return j;
}

int binarize(int n, int binCoin[8])
{
    int i = 0;
    while (n != 0)
    {
        binCoin[i++] = n % 2;
        n /= 2;
    }
    
    for(int j = i; j < 8; j++)
    binCoin[j] = 0;

}

void sort(int arr[8])
{
    for (int i = 0; i < 8; i++)
    {
        for(int j = 7; j > i; j--)
        {
            if (arr[j] > arr[i])
            {
                int t = arr[j];
                arr[j] = arr[i];
                arr[i] = t;
            }
        }
    }
}