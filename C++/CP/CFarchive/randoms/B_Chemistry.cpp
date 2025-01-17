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
        int n, k;cin>>n>>k;
        string s; cin >> s;
        int outLen = n-k;
        unordered_map<char, int> mp;
        for(auto x: s) mp[x]++;
        if(outLen&1){
            int flag = 1;
            int oflag = 1;
            for(auto x: mp){
                if(x.second&1){
                    if(oflag) oflag = 0;
                    else k--;
                }
                if(k<0){
                    flag = 0;
                    break;
                }
            }
            if(flag) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        else{
            int flag = 1;
            for(auto x: mp){
                if(x.second&1){
                    k--;
                }
                if(k<0){
                    flag = 0;
                    break;
                }
            }
            if(flag) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}