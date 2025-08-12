#include<stdio.h>
#include<math.h>

// func to return area of trunk with ki as k
long long int area(long long int l){
    long long int k=pow(2,2*l);
    return k;
}

int main (){

    long long int n;
    while(1){
        //Taking the no. of trunks with different sizes
        // printf("\n Enter the No. Of Different Size Of Trunk : ");
        scanf("%lld",&n);
        if (n>=1 && n<=100000)
            break;
        else{
            printf("%lld",n);
            printf("\n Error, Value not correct. Write Again");
        }
    }
    
    printf("\n ");

    
    long long int T[n][3];// defined a array to store the value of ki & ai


    // printf("\n Enter the : \n");
    for (int i=0; i<n;i++){
        long long int ki,ai;//defining the ki & ai as integer 

        //Taking the value of power level of the trunk
        while(1){
            // printf("\n     Power Level of Trunk %d : ",i+1);
            scanf("%lld",&ki);
            if (ki>=0 && ki<=1000000)
                break;
            else{    
                printf("%lld",ki);
                printf("\n Error, Value not correct. Write Again");
            }
        }
        
        //Taking the no. of trunks of that size
        while(1){
            // printf("\n   No. of Trunk of size 2^%d : ",ki);
            scanf("%lld",&ai);

            if (ai>=1 && ai<=1000000)
                break;
            else{
                printf("%lld",ai);
                printf("\n Error, Value not correct. Write Again");
            }
        }
        
        printf("\n");
        //Now, Storing the ki & ai directly in T array 
        T[i][0]=ki;
        T[i][1]=ai;
    }


    //Used Selection Sort to Sort the array
    int min_indx=0;

    for(int i=0; i<n ;i++ ){
        min_indx=i;
        for (int j=i; j<n ;j++ ){
            if (T[min_indx][0] > T[j][0])
                min_indx=j;
        }
        
        //Swaping the Value of ki and ai of the array
        long long int p=T[min_indx][0];
        long long int q=T[min_indx][1];
        T[min_indx][0]=T[i][0];
        T[min_indx][1]=T[i][1];
        T[i][0]=p;
        T[i][1]=q;

    }

    //Loop for storing the Total Area of all the trunks of the same size
    for ( int i=0; i<n ; i++){
        T[i][2]= area(T[i][0]) * T[i][1];
    }


    long long int S=0;
    for (int i=n-1;i>=0;i--){

        if (T[i][1]==0)
            continue;

        for(int j=i+1;j<n;j++){

            if (T[j][2]==0 )
                continue;
            //Getting how much the trunk can store
            long long int y = T[j][2]/(area(T[i][0])) ;
            
            //Difference of how much it can store & Actual no. of we want to store
            long long int D= y - T[i][1];

            if (D>=0){
                T[j][2] -= (T[i][1] * (area(T[i][0]))) ;
                T[i][1]=0;
            }

            else if (D<0){
                T[j][2] -= (y * (area(T[i][0]))) ;
                T[i][1]=(-1)*D;
            }

        }
        //Storing All the area which can't be stored in any other trunks
        S += T[i][1]*(area(T[i][0]));
    }

    //Finding The Value of P who's area will be greater than S.
    for (int i=n;;i++){
        long long int k=pow(2,2*i);
        if (S <= k){
            printf("%d",i);
            break;
        }
    }

}