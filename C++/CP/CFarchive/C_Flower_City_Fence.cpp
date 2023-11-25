#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pub push_back
#define pob pop_back
#define ff first
#define ss second
#define sz(x) (ll)x.size()
#define all(x) (x).begin(), (x).end()
#define arrIn(arr, n) for(ll i = 0; i < n; i++) cin >> arr[i]
#define vIn(v, n) for(ll i = 0; i < n; i++) { ll temp; cin >> temp; v.pub(temp); }

#define fastio() ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<ll> vi;
typedef vector<vector<ll>> vvi;
typedef map<ll, ll> mpii;
typedef unordered_map<ll, ll> umpii;

const ll M = 1e9+7;
const ll m = 998244353;

int main(){
    fastio();
    int t; cin >> t;
    while(t--){
        ll n;cin>>n;
        vi v;
        vi vtemp;
        for(ll i = 0; i < n; i++){
            ll temp; cin >> temp;
            v.pub(temp);
            vtemp.pub(temp);
        }
        if(v[0] != sz(v)){
            cout << "NO" << endl;
            continue;
        }
        ll vflip[n];
        for(int i = 0; i < n; i++){
            vflip[i]=0;
        }
        for(auto x: v){
            while(x--){
                vflip[x]++;
            }
        }
        int flag = 1;
        for(ll i = 0; i < n; i++){
            if(v[i] != vflip[i]){
                flag = 0;
                break;
            }
            // cout << v[i] << " " << vflip[i] << endl;
        }
        // cout << endl;
        if(flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}