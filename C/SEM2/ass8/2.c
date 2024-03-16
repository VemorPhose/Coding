#include <stdio.h>
#include <stdlib.h>
int* pushA(int* arr,int* p_topA,int* p_topB)
{
    if(*p_topA+1 == *p_topB)
    {
        printf("Overflow\n");
        return arr;
    }
    printf("Enter the value u want to push : ");
    int data;
    scanf("%d",&data);
    arr[++*p_topA] = data;
    return arr;
}
int* pushB(int* arr,int* p_topA,int* p_topB)
{
    if(*p_topA == *p_topB-1)
    {
        printf("Overflow\n");
        return arr;
    }
    printf("Enter the value u want to push : ");
    int data;
    scanf("%d",&data);
    arr[--*p_topB] = data;

    return arr;
}
int* popA(int* arr,int* p_topA)
{
    if(*p_topA <= -1)
    {
        printf("Underflow\n\n");
        return arr;
    }
    printf("%d Popped!\n",arr[*p_topA]);
    *(p_topA)--;
    return arr;
}
int* popB(int* arr,int* p_topB,int n)
{
    if(*p_topB >= n)
    {
        printf("Underflow\n\n");
        return arr;
    }
    printf("%d Popped!\n",arr[*p_topB]);
    *(p_topB)++;
    return arr;
}
void main(void)
{
    int n;
    printf("Enter the size of array : ");
    scanf("%d",&n);
    int topA = -1;
    int topB = n;
    int size = n ;
    int* arr = (int*)calloc(n,sizeof(int));
    printf("\n");
    printf("1. Push in Stack A.\n");
    printf("2. Push in Stack B.\n");
    printf("3. Pop in Stack A.\n");
    printf("4. Pop in Stack B.\n");
    printf("0. EXIT.\n\n");

    while(1)
    {
        int n ;
        printf("Enter your response : ");
        scanf("%d",&n);
        if(n==0)
        {
            break;
        }
        switch(n)
        {
        case 1 :
            arr = pushA(arr,&topA,&topB);
            break;
        case 2 :
            arr = pushB(arr,&topA,&topB);
            break;
        case 3 :
            arr = popA(arr,&topA);
            break;
        case 4 :
            arr = popB(arr,&topB,size);
            break;
        default :
            printf("enter something dawg\n\n");
            break;
        }
        printf("\n");
    }
}
