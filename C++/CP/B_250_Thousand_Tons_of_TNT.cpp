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
        vector<ll> arr;
        for(ll i = 0; i < n; i++){
            ll temp; cin >> temp;
            arr.pub(temp);
        }
        // sort(arr.begin(), arr.end());

        vector<ll> v;
        for(ll i = 1; i < n; i++){
            if(n%i==0) v.pub(i);
        }

        ll out = 0;
        ll maxs = LLONG_MIN;
        ll mins = LLONG_MAX;
        for(auto x: v){
            maxs=LLONG_MIN;
            mins=LLONG_MAX;
            for(ll i = 0; i < n/x; i++){
                ll temp = 0;
                for(ll j = 0; j < x; j++){
                    temp += arr[i*x + j];
                }
                if(temp < mins) mins = temp;
                if(temp > maxs) maxs = temp;
            }
            // cout << maxs << " " << mins << endl;
            if(maxs-mins>out) out=maxs-mins;
        }
        cout << out << endl;
    }
    return 0;
}