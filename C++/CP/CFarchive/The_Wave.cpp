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
    int n,q;cin>>n>>q;
    vector<int> v;
    for(int i = 0; i < n; i++){
        int temp;cin>>temp;
        v.pub(temp);
    }
    sort(all(v));
    // make binary search function
    // for each query, find upper and lower bound
    // if same, number is one of roots i.e. f(x) = 0
    // else, from wavy curve method, find which interval it lies in
    // print positive or negative accordingly.
    while(q--){
        int qn; cin >> qn;
        if(qn > v.at(v.end()-1)){
            cout << "POSITIVE" << endl;
            continue;
        }
        if(qn < v[0]){
            if(n&1) cout << "NEGATIVE" << endl;
            else cout << "POSITIVE" << endl;
            continue;
        }
        int u = upper_bound(all(v), qn);
        int l = lower_bound(all(v), qn);
        if((u != l) || (u == v.end)){
            cout << 0 << endl;
            continue;
        }
        int uIndex = v.find(all(v), u) - v.begin();
        if(uIndex&1) cout << "POSITIVE" << endl;
        else cout << "NEGATIVE" << endl;
    }
    return 0;
}