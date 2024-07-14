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
        int arr[n]; arrIn(arr, n);
        unordered_map<int, int> mp;
        for(auto x: arr) mp[x]++;
        int flag = 2;
        for(auto x: mp) if(x.second > 1) flag--;
        if(flag > 0) cout << -1 << endl;
        else{
            int uniqUsed = 0;
            unordered_set<int> sUsed;
            for(int i = 0; i < n; i++){
                if(mp[arr[i]] < 2) cout << "1 ";
                else{
                    if(!uniqUsed){
                        uniqUsed = arr[i];
                        cout << "2 ";
                    }
                    else if(uniqUsed == arr[i]){
                        cout << "1 ";
                    }
                    else if(find(all(sUsed), arr[i]) != sUsed.end()){
                        cout << "1 ";
                    }
                    else{
                        sUsed.insert(arr[i]);
                        cout << "3 ";
                    }
                }
            }
            cout << endl;
        } 
    }
    return 0;
}