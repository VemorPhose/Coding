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
        int n,k;cin>>n>>k;
        int arr[n];
        for(int i = 0; i < n; i++){
            int temp; cin >> temp;
            temp %= k;
            arr[i] = temp;
        }
        sort(arr, arr + n);
        if(arr[0]==0) cout << 0 << endl;
        else{
            if(k==4){
                int cnt2 = 0, cnt1 = 0;
                for(auto x: arr){
                    if(x==1) cnt1++;
                    if(x==2) cnt2++;
                    if(cnt2>=2) break;
                }
                if(cnt2>=2) cout << 0 << endl;
                else if(arr[n-1]==3) cout << 1 << endl;
                else if(cnt2>=1 && cnt1) cout << 1 << endl;
                else if(cnt1>=2) cout << 2 << endl;
                else cout << 3 << endl;
            }
            else cout << k-arr[n-1] << endl;
        }
    }
    return 0;
}