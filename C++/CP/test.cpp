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

bool cmpp(const pair<int, int> a, const pair<int, int> b){
    if(a.first != b.first) return a.first<b.first;
    return a.second<b.second;
}

int main(){
    fastio();
    vector<pair<int, int>> v;
    int t; cin >> t;
    while(t--){
        char c; cin >> c;
        int m,n;cin>>m>>n;
        auto p = make_pair(m, n);
        v.pub(p);
        v.pub({n,m});
        sort(all(v), cmpp);
        for(auto x: v) cout << x.first << " " << x.second << endl;
    }
    return 0;
}