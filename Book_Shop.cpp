#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

// typedefs
#define ll              int64_t
#define ull             uint64_t
#define Int             int32_t
#define uint            uint32_t
#define pii             pair<int, int>
#define vi              vector<int>
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

vector<vector<int> > dp(1005, vector<int>(100005));

int main(){
    fastio();
    int n, x; cin >> n >> x;
    vi prices; vIn(prices, n);
    vi pages; vIn(pages, n);
    vector<pii> books;
    FOR (i, 0, n) books.pub(mp(prices[i], pages[i]));
    sort(all(books), [](const auto a, const auto b) {
        return a.ff < b.ff;
    });
    if (x < books[0].ff) {
        cout << 0 << endl;
        return 0;
    }
    
    FOR(i, 0, n-1) {
        dp[i][books[i].ff] = max(dp[i][books[i].ff], books[i].ss);
        FOR(j, 0, x+1) {
            if (dp[i][j] != 0) {
                dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
                if (j + books[i+1].ff <= x) {
                    dp[i+1][j + books[i+1].ff] = max(dp[i+1][j + books[i+1].ff], dp[i][j] + books[i+1].ss);
                }
            }
        }
    }
    int maxPages = 0;
    F0R(i, x+1) maxPages = max(maxPages, dp[n-1][i]);
    cout << maxPages << endl;
    return 0;
}
