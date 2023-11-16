#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void bin_to_dec(int m, int arr[][8], int num); // Prototype of the function for converting binary to decimal
void decimalToBinary(int decimalArray[], int times); // Prototype of the function for converting decimal to binary
void min_notes(int notes[], int numNotes, int target, int count[]); //Prototype of the function for finding minimum notes
void bubble_sort(int new_curr[], int length); // Prototype of the function for sorting the array ekements
int main()
{
    int notes[] = {100, 50, 20, 10, 5, 2, 1}; // Earth currency
    int numNotes = sizeof(notes) / sizeof(notes[0]); // length of the array
    int target, j, times = 0;
    int arr[100];

    // printf("Enter the target value: ");
    scanf("%d", &target);
    int count[numNotes];

    min_notes(notes, numNotes, target, count); // calling the function

    for (j = 0; j < numNotes; j++)
    {
        if (count[j] == 1)
        {
            if (notes[j] != 0)
            {
                arr[times] = notes[j];
            }
            times = times + 1;
        }
        else if (count[j] > 1)
        {
            while (count[j] >= 1)
            {
                arr[times] = notes[j];
                if (notes[j] != 0)
                {
                    times += 1;
                }
                count[j]--;
            }
        }
    }
    decimalToBinary(arr, times); // calling the function

    return 0;
}
void bubble_sort(int new_curr[], int length){ // function for sorting the final elements of output arraY
    int temp = 0;

    for (int i = 0; i < length; i++) {   
        for (int j = 0; j < length-i-1; j++) {   
           if(new_curr[j+1] > new_curr[j]) {  
               temp = new_curr[j+1];  
               new_curr[j+1] = new_curr[j];  
               new_curr[j] = temp;  
           }   
        }   
    } 
    printf("\n");   
    for (int i = 0; i < length; i++) { 
        if(new_curr[i] == 0)
        continue;  
        printf("%d ", new_curr[i]);  
    }    
}   
void bin_to_dec(int m, int arr[][8], int num) // function for converting binary to decimal
{
    int x = 8 - num,length=0;
    int new_curr[8] = {0};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            new_curr[i] = new_curr[i] + arr[i][j] * pow(2, (7 - j));
        }

        new_curr[i] = new_curr[i] / (pow(2, x));
    }
    for (int i = 7; i >= 0; i--)
    {
        if (new_curr[i] != 0)
        {
            length++;

        }
        
    }
    bubble_sort(new_curr,8); // calling the function
    return;
}

void decimalToBinary(int decimalArray[], int times) // function for converting decimal to binary
{
    int BinaryArray[8][8] = {0};
    int col = 0;

    for (int i = 0; i < times; i++)
    {
        int decimal = decimalArray[i];
        for (int j = 7; j >= 0; j--)
        {
            int k = (decimal >> j) & 1;
            BinaryArray[i][j] = k;
        }
        col++;
    }
    int new_arr[8][8] = {0};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < times; j++)
        {
            new_arr[8 - i - 1][j] = BinaryArray[j][i];
        }
    }

    bin_to_dec(8, new_arr, col); // calling the function
}

void min_notes(int notes[], int numNotes, int target, int count[]) // function for finding the least amount of earth currency used whose sum is equal to the target value
{
    for (int i = 0; i < numNotes; i++)
    {
        count[i] = target / notes[i];
        target %= notes[i];
    }    
}