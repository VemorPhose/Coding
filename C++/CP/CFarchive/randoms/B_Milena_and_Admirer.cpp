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
        vector<int> v;
        for(int i = 0; i < n; i++){
            int temp; cin >> temp;
            v.pub(temp);
        }
        int prev = v[v.size()-1];
        int cnt = 0;
        for(int i = v.size()-1; i > 0; i--){
            if(v[i-1]>prev){
                if(prev >= (v[i-1]+1)/2){
                    prev=v[i-1]/2;
                    cnt++;
                }
                else{
                    cnt += ceil((v[i-1]*1.0)/prev) - 1;
                    // cout << ceil((v[i-1]*1.0)/prev) - 1 << ",";
                    int temp = v[i-1]%prev;
                    if(temp == 0) temp = prev;
                    // cout << temp << ",";
                    prev = temp;
                }
            }
            else prev = v[i-1];
            // cout << prev << "," << cnt << " ";
        }
        cout << cnt << endl;
    }
    return 0;
}