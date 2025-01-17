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
    vi v[9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            int temp; cin >> temp;
            v[i].pub(temp);
        }
        sort(all(v[i]));
    }
    int flag = 1;
    for(int i = 0; i < 8; i++){
        if(v[i] != v[i+1]){flag = 0; break;}
    }
    cout << flag << endl;
    return 0;
}