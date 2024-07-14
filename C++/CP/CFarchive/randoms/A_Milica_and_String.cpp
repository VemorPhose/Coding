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
        string s; cin >> s;
        vector<int> v;
        for(int i = 0; i < s.size(); i++){
            if(s[i]=='B'){
                if(i!=0) v.pub(v[i-1] + 1);
                else v.pub(1);
            }
            else{
                if(i==0) v.pub(0);
                else v.pub(v[i-1]);
            }
        }
        int numB = v[v.size()-1];
        // cout << numB << endl;
        int reqSub = numB - k;
        if(reqSub==0) cout << 0 << endl;
        else if(reqSub > 0){
            cout << 1 << endl;
            for(int i = 0; i < v.size(); i++){
                if(v[i]==reqSub){
                    cout << i+1 << " " << "A" << endl;
                    break;
                }
            }
        }
        else{
            cout << 1 << endl;
            int cnt = 0;
            reqSub = abs(reqSub);
            for(int i = 0; i < s.size(); i++){
                if(s[i]=='A') cnt++;
                if(cnt==reqSub){
                    cout << i+1 << " " << "B" << endl;
                    break;
                }
            }
        }
    }
    return 0;
}