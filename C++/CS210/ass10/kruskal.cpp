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
vector<pair<int, int> > g[N]; // input graph

int rankNode[N], parent[N];
vector<pair<int, int> > ans[N]; // MST

int find(int u) {
    if (parent[u]!= u) parent[u] = find(parent[u]);
    return parent[u];
}

void unionSet(int u, int n) {
    int uRoot = find(u), vRoot = find(n);
    if (rankNode[uRoot] < rankNode[vRoot]) {
        parent[uRoot] = vRoot;
        rankNode[vRoot] += rankNode[uRoot];
    }
    else {
        parent[vRoot] = uRoot;
        rankNode[uRoot] += rankNode[vRoot];
    }
}

int main(){
    fastio();
    int n, m; cin >> n >> m;
    vector<pair<pair<int, int>, int> > edges, MSTedges;
    int szMSTedges = 0;
    FOR (i, 0, m) {
        int u, v, w; cin >> u >> v >> w;
        g[u].pub(mp(v, w));
        g[v].pub(mp(u, w));
        edges.pub(mp(mp(u, v), w));
    }

    sort(all(edges), [](const auto p1, const auto p2) {
        return p1.ss < p2.ss;  // sort by weight
    });

    FOR (i, 0, n) {
        rankNode[i] = 1;
        parent[i] = i;
    }

    // Kruskal's Algorithm
    for (auto p: edges) {
        if (szMSTedges == n-1) break;  // MST formed
        int u = p.ff.ff, v = p.ff.ss, w = p.ss;
        if (find(u) != find(v)) {
            unionSet(u, v);
            ans[u].pub(mp(v, w));
            ans[v].pub(mp(u, w));
            MSTedges.pub(p);
            szMSTedges++;
        }
    }

    for (auto p: MSTedges) {
        cout << p.ff.ff << " " << p.ff.ss << " " << p.ss << endl;
    }

    return 0;
}
