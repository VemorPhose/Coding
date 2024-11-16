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

const int N = 1e7 + 10;
vector<pair<int, int> > g[N], ans[N]; // MST
bool vis[N];
int wt[N];

struct Comparator {
    bool operator() (pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        return a.ss > b.ss;
    }
};

// FIX THIS SHIT

int main(){
    fastio();
    int n, m; cin >> n >> m;
    FOR (i, 0, m) {
        int u, v, w; cin >> u >> v >> w;
        g[u].pub(mp(v, w));
        g[v].pub(mp(u, w));
    }

    // Prim's algorithm
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int> >, Comparator> q;

    vector<pair<pair<int, int>, int> > MSTedges;
    int szMSTedges = 0;

    vis[0] = true;
    FOR (i, 1, n) wt[i] = INT_MAX;
    for (auto x: g[0]) {
        if (wt[0] + x.ss <= wt[x.ff]) {
            wt[x.ff] = wt[0] + x.ss;
            q.push(mp(mp(0, x.ff), wt[x.ff]));
        }
    }

    while (!q.empty()) {
        auto x = q.top(); q.pop();
        if (vis[x.ff.ss]) continue;
        vis[x.ff.ss] = true;
        ans[x.ff.ff].pub(mp(x.ff.ss, abs(wt[x.ff.ss]-wt[x.ff.ff])));
        ans[x.ff.ss].pub(mp(x.ff.ff, abs(wt[x.ff.ss]-wt[x.ff.ff])));
        MSTedges.pub(mp(mp(x.ff.ff, x.ff.ss), abs(wt[x.ff.ss]-wt[x.ff.ff])));
        szMSTedges++;
        for (auto y: g[x.ff.ss]) if (!vis[y.ff]) q.push(mp(mp(x.ff.ss, y.ff), wt[x.ff.ss]+y.ss));
    }

    for (auto p: MSTedges) {
        cout << p.ff.ff << " " << p.ff.ss << " " << p.ss << endl;
    }

    return 0;
}
