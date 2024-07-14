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
        if(c=='+') v.pub(p);
        else{
            auto it = find(all(v), p);
            v.erase(it);
        }
        int flag = 1;
        if(sz(v)<=1){
            cout << "NO" << endl;
            continue;
        }
        else{
            sort(all(v), cmpp);
            int lcur=0,rcur=0;
            for(auto x: v){
                if((lcur==0)||(x.first > rcur)){
                    lcur=x.first;
                    rcur=x.second;
                    continue;
                }
                flag = 0;
                break;
            }
            if(flag==0) cout << "NO" << endl;
            else cout << "YES" << endl;
        }
    }
    return 0;
}