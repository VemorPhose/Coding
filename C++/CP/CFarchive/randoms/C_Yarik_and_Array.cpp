#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD int(1e9 + 7)
#define pub push_back
#define pob pop_back
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()
#define arrIn(arr, n) for(int i = 0; i < n; i++) cin >> arr[i]

#define fastio() ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

int main(){
    fastio();
    int t; cin >> t;
    while(t--){
        int n; cin >>n;
        vector<int> v;
        vector<int> presum;
        for(int i = 0; i < n; i++){
            int temp; cin>>temp;
            v.pub(temp);
        }
        for(int i = 0; i < n; i++){
            if(i==0) presum.pub(v[i]);
            else if((abs(v[i])&1 && (!(abs(v[i-1])&1)))||(abs(v[i-1])&1 && (!(abs(v[i])&1)))){
                if(v[i]+presum[i-1]>v[i]) presum.pub(v[i]+presum[i-1]);
                else presum.pub(v[i]);
            }
            else presum.pub(v[i]);
        }
        // for(auto x: presum) cout << x << " ";
        // cout << endl;
        sort(all(presum), greater<int>());
        cout << presum[0] << endl;
    }
    return 0;
}