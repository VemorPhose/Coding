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

int substrCheck(string x, string s){
    // for(int i = 0; i < x.length(); i++){
    //     for(int j = i; j < x.length(); j++){
    //         if(x.substr(i, j-i+1) == s){
    //             return 1;
    //         }
    //     }
    // }
    if (x.find(s) != string::npos)
        return 1;
    return 0;
}

int main(){
    int t; cin >> t;
    while(t--){
        int n, m; cin>>n>>m;
        string x, s;cin>>x>>s;
        int counter = 0;
        while(true){
            if(substrCheck(x, s)){
                cout << counter << endl;
                break;
            }
            else if(x.length() > s.length() && counter >= 8){
                cout << -1 << endl;
                break;
            }
            else{
                x += x;
                counter++;
            }
        }
    }
    return 0;
}