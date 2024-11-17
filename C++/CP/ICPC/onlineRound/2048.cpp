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

const int MAXN = 4000005;
int dp[MAXN];
 
int main() {
    fastio();
    
    int t;
    cin >> t;
    vector<int> queries(t);
    for(int i = 0; i < t; i++) {
        cin >> queries[i];
    }
    vi pows;
    ll num = 4;
    while(num < MAXN) {
        num*=4;
        pows.pub(num);
    }
    // cout << sz(pows) << endl << endl;
    dp[0] = 1;
    // FOR (i, 1, MAXN) {
    //     if (i%4 != 0) continue;
    //     for (auto x: pows) {
    //         if (i-x > 0) {
    //             dp[i] = (dp[i] + dp[i-x]) % mod;
    //         }
    //         else break;
    //     }
    // }
    for (auto x: pows) {
        FOR (i, 1, MAXN) {
            if (i%4 != 0) continue;
            if (i-x >= 0) {
                dp[i] = (dp[i] + dp[i-x]) % mod;
            }
            else continue;
        }
    }
    FOR (i, 0, 35) cout << i << " " << dp[i] << endl;
    cout << endl;
    cout << dp[128] << endl << endl;
    for (auto x: queries) cout << dp[x] << endl;

    // for (auto x: queries) {
    //     if (x%4 != 0) {
    //         cout << 0 << endl;
    //         continue;
    //     }
    //     ll ans = 1;
    //     for (auto y: pows) {
    //         ans += x/y;
    //         ans %= mod;
    //     }
    //     cout << ans << endl;
    // }
    return 0;
}