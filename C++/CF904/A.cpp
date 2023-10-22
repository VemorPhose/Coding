#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define MOD int(1e9 + 7)
#define pub push_back
#define pob pop_back
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()
#define arrIn(arr, n) for(int i = 0; i < n; i++) cin >> arr[i]

#define fastio() ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;

int main(){
    fastio();
    int t; cin >> t;
    while(t--){
        int x, k; cin >> x >> k;
        while(true){
            vector<int> v;
            int temp = x;
            while(temp){
                v.pub(temp%10);
                temp/=10;
            }
            int sum = accumulate(all(v), 0);
            // cout << sum << endl;
            if(sum%k == 0){
                cout << x << endl;;
                break;
            }
            x++;
        }
    }
    return 0;
}