#include<stdio.h>
#include<math.h>
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    int rs[m];
    int cs[n];

    // Take the row sums as input
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &rs[i]);
    }

    // Take the column sums as input
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cs[i]);
    }

  int arr[m][n];int k;
  for(int i=0;i<m;i++)
  {


      for(int j=0;j<n;j++)
      {
        k=cs[j]<rs[i]?cs[j]:rs[i];//checking min of sum of row and sum of column
        arr[i][j]=k;
        rs[i]-=k;//updating sum of row
        cs[j]-=k;//updating sum of column
      }

  }
  for(int i=0;i<m;i++)
  {


      for(int j=0;j<n;j++)
      {
          printf("%d ",arr[i][j]);  //printing the array
      }
      printf("\n");


}
}