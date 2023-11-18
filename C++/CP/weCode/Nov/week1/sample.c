#include<stdio.h>
int main(){
    int N;
    // printf("ENTER AMOUNT OF MONEY : ");
    scanf("%d", &N);
    int N1=N;
    int numberOfSteps=0;
    while(N1>0){
        if(N1>=100){
            N1=N1-100;
        }
        else if(N1<100 && N1>=50){
            N1=N1-50;
        }
        else if(N1<50 && N1>=20){
            N1=N1-20;
        }
        else if(N1<20 && N1>=10){
            N1=N1-10;
        }
        else if(N1<10 && N1>=5){
            N1=N1-5;
        }
        else if(N1<5 && N1>=2){
            N1=N1-2;
        }
        else if(N1<2 && N1>=1){
            N1=N1-1;
        }
        numberOfSteps++;
    }
    int N2=N;
    int D[numberOfSteps];
    for(int k=0;k<=(numberOfSteps-1);k++){
        if(N2>=100){
            N2=N2-100;
            D[k]=100;
        }
        else if(N2<100 && N2>=50){
            N2=N2-50;
            D[k]=50;
        }
        else if(N2<100 && N2>=50){
            N2=N2-50;
            D[k]=50;
        }
        else if(N2<50 && N2>=20){
            N2=N2-20;
            D[k]=20;
        }
        else if(N2<20 && N2>=10){
            N2=N2-10;
            D[k]=10;
        }
        else if(N2<10 && N2>=5){
            N2=N2-5;
            D[k]=5;
        }
        else if(N2<5 && N2>=2){
            N2=N2-2;
            D[k]=2;
        }
        else if(N2<2 && N2>=1){
            N2=N2-1;
            D[k]=1;
        }
    }
    int m;
    int a[8][numberOfSteps];
    for(int i=0;i<=(numberOfSteps-1);i++){
        m=128;
        for(int j=0;j<=7;j++){
            if(D[i]>=m){
            a[j][i]=1;
        }
        if(D[i]<m){
            a[j][i]=0;
        }
        if(a[j][i]==1){
            D[i]=D[i]-m;
        }
        m=m/2;
        }
    }
    int A[8];
    for(int Y=0;Y<=7;Y++){
        A[Y]=0;
    }
    int M;
    for(int K=0;K<=7;K++){
        M=1;
        for(int J=(numberOfSteps-1);J>=0;J--){
            A[K]=A[K]+(M*a[K][J]);
            M=M*2;
        }
    }
    int COUNT=0;
    int count=0;
    while(COUNT<=7){
        if(A[COUNT]!=0){
            count++;
        }
        COUNT++;
    }
    int I[count];
    int R=0;
    int H=0;
    while(H<=7){
        if(A[H]!=0){
            I[R]=A[H];
            R++;
        }
        H++;
    }
    int temp;
    for(int p=0;p<=(count-1);p++){
        for(int P=p;P<=(count-1);P++){
            if(I[p]<I[P]){
                temp=I[p];
                I[p]=I[P];
                I[P]=temp;
            }
        }
    }
    for(int Q=0;Q<=(count-1);Q++){
        printf("%d ", I[Q]);
    }
    return 0;
}