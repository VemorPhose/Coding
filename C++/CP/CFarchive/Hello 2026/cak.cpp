// 雪雁不浴自白，人亦无为而自成。
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <cmath>
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

int main(){
    fastio();
    ll t; cin >> t;
    while(t--){
        ll n,m,k; cin>>n>>m>>k;

        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        if (m == 1) {
            cout << 2 << endl;
            continue;
        }

        ll l = k-1, r = n-k;
        ll b = max(l, r), s = min(l, r);
        ll res = 1;
        // cout << " " << s << " " << b << endl;

        // if(s == 0) {
        //     cout << min(n, (m+1)/2 + 1) << endl;
        //     continue;
        // }

        // if ((2*s-1) >= m) {
        //     if (m&1) cout << (m+1)/2 + 1 << endl;
        //     else cout << (m+1)/2 + 2 << endl;
        //     continue;
        // }

        // res += s;
        // ll cur = s-1;
        // if (s == 1) cur = 1;
        // // cout << endl; 
        // ll ml = m - 2*s + 1;
        // // cout << " " << cur << " " << ml << endl;
        // cur += max(0LL, (ml-cur)/2);
        // res += min(b, cur);
        // // cout << " " << cur << " " << ml << endl;
        // cout << res << endl;
        
        // // if (m <= s*s*2) {
        // //     cout << floor(sqrt(m))*2 + 1 << endl;
        // //     continue;
        // // }
        // // cout << endl;
        

        if (s==0) {
            cout << min(n, (m+1)/2+1) << endl;
            continue;
        }

        if ((2*s-1) >= m) {
            if (m&1) cout << (m+1)/2 + 1 << endl;
            else cout << (m+1)/2 + 2 << endl;
            continue;
        }
    }
    return 0;
}
