#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

// typedefs
#define ll              int64_t
#define ull             uint64_t
#define Int             int32_t
#define uint            uint32_t
#define pii             pair<ll, ll>
#define vi              vector<ll>
#define vvi             vector<vector<ll>>
#define mpii            map<ll, ll>
#define umpii           unordered_map<ll, ll>
#define vs              vector<string>

// shortcuts
#define MOD             1000000007
#define mod             998244353
#define INF             1000000000000000010
#define PI              2 * acos(0.0)
#define LL_MAX          LLONG_MAX
#define LL_MIN          LLONG_MIN
#define ULL_MAX         ULLONG_MAX
#define endl            "\n"

// binary operations
#define swap(a,b)       a=a^b; b=b^a; a=a^b
#define setibit(n,i)    (n | (1<<i))
#define extibit(n,i)    (n & (1<<i))
#define clribit(n,i)    (n & ~(1<<i))
#define invibit(n,i)    (n ^ (1<<i))
#define setbits(x)      __builtin_popcountll(x)
#define lzbits(x)       __builtin_clzll(x)
#define tzbits(x)       __builtin_ctzll(x)

// pairs
#define ff              first
#define ss              second
#define mp              make_pair

// iterable operations
#define pub             push_back
#define pob             pop_back
#define ft              front()
#define bk              back()
#define ins             insert
#define sz(x)           (ll)x.size()
#define all(x)          (x).begin(), (x).end()

// looping
#define FOR(i, a, b)    for (ll i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)
#define ROF(i, a, b)    for (ll i = (b)-1; i >= (a); --i)
#define R0F(i, a)       ROF(i, 0, a)

// general
#define fastio()        ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define arrIn(arr, n)   for(ll i = 0; i < n; i++) cin >> arr[i]
#define vIn(v, n)       for(ll i = 0; i < n; i++) { ll temp; cin >> temp; v.pub(temp); }
#define coutN           cout << "NO" << endl
#define coutY           cout << "YES" << endl

const int N = 1000000;
int arr[N], pre[N], suf[N];

int main(){
    fastio();
    ll t; cin >> t;
    while(t--){
        string s; cin >> s;
        int n = s.size();
        memset(arr, 0, sizeof(arr));
        memset(pre, 0, sizeof(pre));
        memset(suf, 0, sizeof(suf));
        FOR (i, 0, n-3) {
            if (s[i]=='1'&&s[i+1]=='1'&&s[i+2]=='0'&&s[i+3]=='0') arr[i] = 1;
        }

        pre[0] = arr[0];
        FOR (i, 1, n) {
            pre[i] = pre[i-1] + arr[i];
        }
        suf[n-1] = arr[n-1];
        ROF (i, n-2, 0) {
            suf[i] = suf[i+1] + arr[i];
        }

        FOR (i, 0, n) cout << pre[i] << " ";
        cout << endl;
        FOR (i, 0, n) cout << suf[i] << " ";
        cout << endl;

        int q; cin >> q;
        while(q--){
            int i; char v; cin >> i >> v;
            s[i-1] = v;
            if (n < 4) {
                coutN;
                continue;
            }
            bool flag = false;
            int start = 0;
            if (i-4 > start) start = i-4;
            int end = n-1;
            if (i+2 > end) end = i+2;
            bool cnt = 0;
            for(int j = start; j <= end; j++){
                if(s[j] == '1'){
                    if (cnt<2) cnt++;
                    else if (cnt > 2) cnt = 1;
                }
                else if(s[j] == '0') {
                    if (cnt == 2) cnt++;
                    else if (cnt == 3) {
                        cnt++;
                        flag = true;
                        break;
                    }
                }
            }
            if(flag) cout << "YES" << endl;
            else if (i-5 >= 0 && pre[i-5] != 0) coutY;
            else if (i+3 <= n-1 && suf[i+3] != 0) coutY;
            else cout << "NO" << endl;
        }
    }
    return 0;
}
