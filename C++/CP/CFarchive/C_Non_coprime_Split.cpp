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
        ll l,r;cin>>l>>r;
        ll out;
        if(l==r && l&1){
            out = r;
            // unordered_map<ll, ll> mp;
            // ll temp = out;
            // while(temp > 1){
            //     for(ll i = 2; i <= temp; i++){
            //         if(temp%i == 0){
            //             mp[i]++;
            //             temp/=i;
            //             break;
            //         }
            //     }
            // }
            int flag = 0;
            // for(auto p: mp){
            //     if(p.second > 1){
            //         cout << p.second << " " << out-p.second << endl;
            //         flag = 1;
            //         break;
            //     }
            // }
            for(int i = 2; i <= sqrt(out); i++){
                if((out-i)%i==0){
                    cout << i << " " << out - i << endl;
                    flag = 1;
                    break;
                }
            }
            if(!flag) cout << -1 << endl;
            continue;
        }
        if(r&1) out = r-1;
        else out = r;
        out/=2;
        if(out==1){
            cout << -1 << endl;
            continue;
        }
        cout << out << " " << out << endl;
    }
    return 0;
}