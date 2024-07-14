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
        vector<string> vs;
        for(int i = 0; i < 8; i++){
            string s; cin >> s;
            vs.pub(s);
        }
        string out = "";
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(vs[i][j]!='.') out.pub(vs[i][j]);
            }
        }
        cout << out << endl;
    }
    return 0;
}