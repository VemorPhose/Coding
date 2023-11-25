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
        int n; cin >> n;
        map<int, int> mp;
        for(int i = 0; i < n; i++){
            int d, s; cin >> d >> s;
            if(mp[d]){
                if(s < mp[d]) mp[d] = s;
                continue;
            }
            mp[d] = s;
        }
        int tleft = INT_MAX;
        int kmax = 0;
        while(tleft > 0){
            kmax++;
            tleft--;
            int temp = mp[kmax];
            if(temp && (temp-1)/2 < tleft) tleft = (temp-1)/2;
        }
        cout << kmax << endl;
    }
    return 0;
}