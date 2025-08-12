#include <stdio.h>
#include <math.h>
int main()
{
    // printf("Enter two number m and n \n");
    int m,n;
    scanf("%d %d",&m,&n);

    for(int i=m;i<=n;i++)
    {
        int s=0,p=1;int c=0;
        for(int j=i;j>0;j/=10)
        {
            int k=j%10;
            s+=k;
            p*=k;
        }
        int x=s+p;
        int rev=0;
        for(int j=x;j>0;j/=10)
        c++;
        c--;
        for(int j=x;j>0;j/=10)
        {
            int k=j%10;
            rev=rev+(k*pow(10,c));
            c=c-1;
        }
        if(rev==x)
        {
        printf("%d \n",i);
        }
    }
}