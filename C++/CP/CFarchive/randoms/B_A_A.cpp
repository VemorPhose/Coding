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
    for(ll i = 0; i < t; i++){
        ll temp = 1;
        for(ll j = 0; j < i; j++){
            temp *= i;
        }
        if(temp==t){
            cout<<i<<endl;
            return 0;
        }
        else if(temp>t || temp < 0){
            cout<<-1<<endl;
            return 0;
        }
    }
    return 0;
}