#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    //Function to return a list of indexes denoting the required 
    //combinations whose sum is equal to given number.
    vector<vector<int> > ans;
    
    void solve(vector<int> &A, int B, vector<int> &out, int curInd){
        if(accumulate(out.begin(), out.end(), 0) == B){
            if(find(ans.begin(), ans.end(), out) == ans.end()) ans.push_back(out);
            return;
        }
        else if(accumulate(out.begin(), out.end(), 0) > B) return;
        for(int i = curInd; i < A.size(); i++){
            out.push_back(A[i]);
            solve(A, B, out, curInd);
            curInd++;
            out.pop_back();
        }
        return;
    }
    
    vector<vector<int> > combinationSum(vector<int> &A, int B) {
        // Your code here
        vector<int> out;
        sort(A.begin(), A.end());
        solve(A, B, out, 0);
        return ans;
    }
};

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> A;
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            A.push_back(x);
        }   
        int sum;
        cin>>sum;
        Solution ob;
        vector<vector<int>> result = ob.combinationSum(A, sum);
   		if(result.size()==0){
   			cout<<"Empty";
   		}
        for(int i=0;i<result.size();i++){
            cout<<'(';
            for(int j=0;j<result[i].size();j++){
                cout<<result[i][j];
                if(j<result[i].size()-1)
                    cout<<" ";
            }
            cout<<")";
        }
        cout<<"\n";
    }
}	