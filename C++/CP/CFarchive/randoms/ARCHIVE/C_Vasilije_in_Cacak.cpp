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
        ll n,k,x;cin>>n>>k>>x;
        ll verstappen = n*(n+1)/2;
        ll sub = (n-k)*(n-k-1)/2;
        if(verstappen-sub >= x) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}