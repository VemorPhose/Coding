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
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        // vector<int> v;
        unordered_map<ll, ll> mp;
        for(ll i = 0; i < n; i++){
            ll temp; cin >> temp;
            // v.pub(temp);
            mp[temp]++;
        }
        ll out = mp[1]*mp[2];
        for(auto x: mp){
            ll cnt = x.second;
            out += (cnt*(cnt-1))/2;
        }
        cout << out << endl;
    }
    return 0;
}