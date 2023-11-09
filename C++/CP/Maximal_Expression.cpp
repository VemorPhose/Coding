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
        int n,k;cin>>n>>k;
        if(2*k > n) cout << n/2 << endl;
        else if(n%k == 0) cout << k/2 << endl;
        
        // else if(k - n%k == 1) cout << (n%k)/2 << endl;
        // else if(n%k <= k/2) cout << (k + n%k)/2 << endl;
        // else cout << k-1 << endl;
        else{
            if(n&1){
                if(n%k <= k/2) cout << (k + n%k)/2 << endl;
                else if(k - n%k == 1) cout << (n%k)/2 << endl;
                else cout << (k + n%k)/2 << endl;
            }
            else{
                if(n%k <= k/2) cout << (k + n%k)/2 << endl;
                else if(k - n%k == 1) cout << (n%k)/2 << endl;
                else cout << (k + n%k)/2 << endl;
            }
        }
    }
    return 0;
}