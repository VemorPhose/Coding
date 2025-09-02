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
        vector<ll> v, vsorted;
        for(ll i = 0; i < n; i++){
            ll temp; cin >> temp;
            v.pub(temp);
            vsorted.pub(temp);
        }
        sort(all(vsorted));
        ll flag = 1;
        auto it = find(all(v), vsorted[0]);
        ll index = (ll)(it - v.begin());
        while(it+1 != v.end()){
            if(*(it) > *(it+1)){
                flag = 0;
                break;
            }
            it++;
        }
        if(flag == 0) cout << -1 << endl;
        else{
            cout << index << endl;
        }
    }
    return 0;
}