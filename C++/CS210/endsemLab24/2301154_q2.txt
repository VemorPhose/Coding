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

int main(){
    fastio();
    ll n, m; cin >> n >> m;
    string s, t;
    if (n > 0) cin >> s;
    if (m > 0) cin >> t;
    vi scost; vIn(scost, n);
    vi tcost; vIn(tcost, m);

    if (n == 0 || m == 0) {
        cout << accumulate(all(scost), 0) + accumulate(all(tcost), 0) << endl;
        return 0;
    }

    ll dp[n+1][m+1];
    FOR (i, 0, n+1) dp[i][0] = 0;
    FOR (i, 0, m+1) dp[0][i] = 0;

    FOR (i, 1, n+1) {
        FOR (j, 1, m+1) {
            if (s[i-1] == t[j-1]) dp[i][j] = max(max(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1] + scost[i-1] + tcost[j-1]);
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    ll totalCost = accumulate(all(scost), 0) + accumulate(all(tcost), 0);
    totalCost = totalCost - dp[n][m];
    cout << totalCost << endl;

    return 0;
}
