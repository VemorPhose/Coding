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
    string s; cin >> s;
    int cnt = 1;
    ll combs = 0;
    for(int i = 1; i < s.size(); i++){
        if(s[i] != s[i-1]){
            combs += (cnt * 1LL * (cnt-1))/2;
            cout << combs << " ";
            cnt = 1;
        }
        else cnt++;
    }
    combs += (cnt * 1LL * (cnt-1))/2;
    cout << combs << " ";
    cnt = 1;
    cout << combs << endl;
    return 0;
}