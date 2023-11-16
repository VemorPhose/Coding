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
    string a,b;cin>>a>>b;
    int flag = 1;
    for(int i = 0; i < sz(a); i++){
        if(tolower(a[i]) < tolower(b[i])){
            cout << -1 << endl;
            flag = 0;
            break;
        }
        else if(tolower(a[i]) > tolower(b[i])){
            cout << 1 << endl;
            flag = 0;
            break;
        }
    }
    if(flag) cout << 0 << endl;
    return 0;
}