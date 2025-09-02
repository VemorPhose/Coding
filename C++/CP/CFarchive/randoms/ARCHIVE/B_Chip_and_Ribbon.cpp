#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pub push_back
#define pob pop_back
#define ff first
#define ss second
#define sz(x) (ll)x.size()
#define all(x) (x).begin(), (x).end()
#define arrIn(arr, n) for(ll i = 0; i < n; i++) cin >> arr[i]
#define vIn(v, n) for(ll i = 0; i < n; i++) { ll temp; cin >> temp; v.pub(temp); }

#define fastio() ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef vector<ll> vi;
typedef vector<vector<ll>> vvi;
typedef map<ll, ll> mpii;
typedef unordered_map<ll, ll> umpii;

const ll M = 1e9+7;
const ll m = 998244353;

int main(){
    fastio();
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        vi v; vIn(v, n);
        int flag = 0;
        ll cnt0 = 0;
        vi temp = v;
        for(auto &x: v){
            if(x==0 && flag==0) flag = 1;
            else if(x==0 && flag==1) continue;
            else if(flag==1){
                cnt0++;
                flag = 0;
            }
        }

        sort(all(temp), greater<int>());
        if(cnt0==0){
            if(!flag) cout << temp[0]-1 << endl;
            else cout << 0 << endl;
            continue;
        }
        // ll min0nt = 0;
        // for(int i = n-1; i >= 0; i--) if(temp[i]!=0) {min0nt = temp[i];break;}

        // for(auto &x: v){
        //     if(x) x-=min0nt;
        // }

        ll cnt = 0;
        // cnt += cnt0*min0nt;
        // cnt += min0nt-1;

        for(int i = 0; i < n; i++){
            flag = 0;
            int breakflag = 1;
            for(auto &x: v){
                if(x==0 && flag==0) flag = 1;
                else if(x==0 && flag==1) continue;
                else if(flag==1){
                    breakflag = 0;
                    cnt++;
                    x--;
                    flag = 0;
                }
                else{
                    x--;
                    breakflag=0;
                }
            }
            if(breakflag){
                cnt--;
                break;
            }
            cnt++;
        }
        cout << cnt << endl;
        // ll out = *max_element(all(v)) - 1;
        // if(cnt==0) cout << out << endl;
        // else if(out==0) cout << cnt << endl;
        // else cout << out*cnt << endl;
    }
    return 0;
}