#include<stdio.h>
#include<string.h>
#include<math.h>
void first();
void outcome(char *arr,int l);
void palindrome(char *arr,int l);
int main()
{ 
  int t;
  scanf("%d",&t);
  while(t--)
  first();
return 0;
}

void first()
  { int l;
    scanf("%d",&l); 
    char str[13];
    
 scanf("%s",str);
 
if(l>=1 && l<=12)
 palindrome(str,l);
else 
printf("-1");
 }
   

void palindrome(char *str,int l)
{   int i,result=0;
    for(i=0;i<l;i++)
    { int a= (int)str[i];
      if(a<123 && a>96 || str[i]=='.')
     {if(str[i] != str[l-1-i] && str[i] != '.' && str[l-1-i] != '.')
        { result = -1;
          break; }
       
        else if(str[i] == '.' || str[l-1-i] == '.')
          { if(str[i] == '.' && str[l-i-1] == '.')
                {str[i] = 'a' ;
                 str[l-i-1] = 'a';}
         
            else if(str[i] != '.' )           
            str[l-i-1] = str[i];
            }}
            else
            result=-1;
    }
    if(result == -1)
     printf("-1\n");
    else
     outcome(str,l);
}

void outcome(char *str,int l)
{  double sum=0;
  for(int i=1;i<l;i++)
    sum=sum+pow(26,i);
  for(long int i=0;i<l-1;i++)
  {  sum=sum+(((int)str[i]-97) * pow(26,l-i-1));
          }  
  
  sum=sum+(int)str[l-1]-96;
  //printf("%lf\n",sum);
  long long int k;
  k=sum;
  printf("%lld\n",k);
}