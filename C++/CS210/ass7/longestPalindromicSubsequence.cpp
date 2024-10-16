#include<bits/stdc++.h>
using namespace std;
#define p(i) pair<i,i>
#define ff first
#define pb push_back
#define ss second
#define v(i) vector<i>
 
int len_odd_palindrome(int arr[],int n, int x)
{
    int len = 1;
    int i = 0;
    int j = 0;
    while(x-i>0 && x+j<n-1)
    {
        if(arr[x-i]==arr[x+j])
        {
            len+=2;
            
        }
        i++;
        j++;
        //else break;
    }
    return len;
}
int len_even_palindrome(int arr[],int n,int x)
{
    if(arr[x]!=arr[x+1])
        return 1;
    int len = 2;
    int i = 1;
    int j = 2;
    while(x-i>0 && x+j<n-1)
    {
        if(arr[x-i]==arr[x+j])
        {
            len+=2;
            
        }
        i++;
        j++;
        //else break;
    }
    return len;
}
int max_len_palindrome(int arr[],int n)
{
    int len =1;
    for(int i=1;i<n-1;i++)
    {
        int odd = len_odd_palindrome(arr,n,i);
        int even = len_even_palindrome(arr,n,i);
 
        len = max(len,odd);
        len = max(len,even);
    }
    return len;
}
int main()
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    cout<<max_len_palindrome(arr,n);
}