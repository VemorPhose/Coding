#include<stdio.h>
main()
{
    int m,n,i,a,b,j,f=1,k=0,c,l;
    // printf("m:");
    scanf("%d",&m);
    // printf("n:");
    scanf("%d",&n);
    if (m<=n)
    {
        if (n<=100000)
        {
            for(i=m;i<=n;i++)
            {
                for(l=m;l>0;l=l/10)
                {
                    c=l%10;
                    f=f*c;
                    k=k+c;
                }
                a=f+k;
                for(j=a;j>0;j=j/10)
                {
                    b=j%10;
                }
                if(b==a)
                    printf("%d \n",i);
            }
        }
        else
            printf("Invalid Input.");

    }
    else
        printf("Invalid Input.");
}