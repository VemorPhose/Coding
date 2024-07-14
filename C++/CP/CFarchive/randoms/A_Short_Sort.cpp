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
        string s; cin >> s;
        if(s == "abc") cout << "YES" << endl;
        else if(s =="acb") cout << "YES" << endl;
        else if(s =="bca") cout << "NO" << endl;
        else if(s =="bac") cout << "YES" << endl;
        else if(s =="cab") cout << "NO" << endl;
        else if(s =="cba") cout << "YES" << endl;  
    }
    return 0;
}