/**
a simple code based on area comparasion of cubes finding the cube with the largest area for nth row.
**/
#include <stdio.h>
#include <math.h>
// BHAIYA 100 MARKS EXPECTED XD
int main()
{
    int n;// to input n
    printf("Enter n\n");
    scanf("%d",&n);
    int ki[n];
    int ai[n];
    for(int i=0;i<n;i++)// user input
    {
        scanf("%d",&ki[i]);
        scanf("%d",&ai[i]);
    }

    //bubble sort both array together
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1-i;j++)
        {
            if(ki[j]>ki[j+1])
            {
                int t1=ki[j];
                ki[j]=ki[j+1];
                ki[j+1]=t1;

                int t2=ai[j];
                ai[j]=ai[j+1];
                ai[j+1]=t2;
            }
        }
    }
    int  max=0;// to find maximum area of blocks
    int area[n];
    for(int i=0;i<n;i++)
    {
        area[i]=ai[i]*pow(2,ki[i])*pow(2,ki[i]);//side*side=cube area || cube area* number of cubes total area of a given cube size
        if(area[i]>max)//max area
            max=area[i];
    }

    int a=0;

    for(int i=0;;i+=2)
    {
        if(max<=pow(2,i))// checking maximum area of a cube just greater than max area
        {
            a=pow(2,i);
            break;
        }
    }


    int side=sqrt(a);//calculating side from area
    int p=0;
    for(int i=0;;i++)
    {
        if(side==pow(2,i))// side in form of 2^n
        {
            p=i;
            break;
        }
    }
    printf("%d \n",p);

    return 0;
}