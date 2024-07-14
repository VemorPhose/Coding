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
        int n,m;cin>>n>>m;
        vector<string> vs;
        for(int i = 0; i < n; i++){
            string temp; cin >> temp;
            vs.pub(temp);
        }
        int cnt = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(cnt==0 && vs[j][i]=='v'){
                    cnt=1;
                    break;
                }
                if(cnt==1 && vs[j][i]=='i'){
                    cnt=2;
                    break;
                }
                if(cnt==2 && vs[j][i]=='k'){
                    cnt=3;
                    break;
                }
                if(cnt==3 && vs[j][i]=='a'){
                    cnt=4;
                    break;
                }
            }
        }
        if(cnt==4) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}