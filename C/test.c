#include<stdio.h>

int fac(int n){
    int f=1,i;
    for(i=1;i<=n;i++){
        f=f*i;
    }
    return f;
}
int numdig(int n){
    int temp=n,a,dig=0;
    while(n>0){
       a=n%10;
       dig++;
       n=n/10;} 
    return fac(dig);
}


int digstore(int n){
    int a,i=0,j,k,dig[i];
    while(n>0){
        dig[i]=n%10;
        n=n/10;
        i++;
    }
    for(j=1;j<i;j++){
        for(int k=0;k<i-j;k++){
            if(dig[k]<dig[k+1]){
                //swap
                int temp=dig[k+1];
                dig[k+1]=dig[k];
                dig[k]=temp;
            }
        }
    }
    printf("max number is : ");
    for(k=0;k<i;k++)
        printf("%d",dig[k]);
    printf("\n");
    return 0;
}

int primeCheck(int n){
    if(n <= 1) return 0;
    int flag = 1;
    for(int i = 2; i < n; i++){
        if(n % i == 0){
            flag = 0;
            break;
        }
    }
    return flag;
}

int main(){
    int N;
    printf("enter number of patients : ");
    scanf("%d",&N);

    printf("possible number of combination :%d\n",numdig(N)); 
    digstore(N);
    for(int i = 1; i <= numdig(N); i++){
        if((i%10 == 3 || i%10 == 7) && primeCheck(i)){
            printf("%d\n", i);
        }
    }
    return 0;    
}