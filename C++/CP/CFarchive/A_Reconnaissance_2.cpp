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
    // int t; cin >> t;
    // while(t--){
    int n;cin>>n;
    int arr[n]; arrIn(arr, n);
    int minh = INT_MAX; pair<int, int> out;
    for(int i = 0; i < n-1; i++){
        if(abs(arr[i+1] - arr[i]) < minh){
            minh = abs(arr[i+1]-arr[i]);
            out = {i+1, i+2};
        }
    }
    if(abs(arr[0] - arr[n-1]) < minh){
        minh = abs(arr[0]-arr[n-1]);
        out = {n, 1};
    }
    cout << out.first << " " << out.second << endl;
    // }
    return 0;
}