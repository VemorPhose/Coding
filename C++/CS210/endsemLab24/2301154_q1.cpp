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
vector<int> g[N];
bool vis[N];
int level[N];

void bfs(vector<int>& sources) {
    queue<int> q;
    for (int vertex : sources) {
        q.push(vertex);
        vis[vertex] = 1;
    }

    while (!q.empty()) {
        int cur_v = q.front();
        q.pop();
        for (int child: g[cur_v]) {
            if (!vis[child]) {
                q.push(child);
                vis[child] = 1;
                // cout << cur_v << " " << child << " " << level[cur_v] + 1 << endl;
                level[child] = level[cur_v] + 1;
            }
        }
    }
}

int main(){
    fastio();
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int s1, s2; cin >> s1 >> s2;
    vector<int> v1; vIn(v1, s1);
    vector<int> v2; vIn(v2, s2);

    FOR (i, 0, n) level[i] = INT_MAX;
    for (auto x: v1) level[x] = 0;
    // FOR (i, 0, n) cout << level[i] << " ";
    // cout << endl;
    bfs(v1);
    // FOR (i, 0, n) cout << level[i] << " ";
    // cout << endl;
    int minDist = INT_MAX;
    for (auto x: v2) minDist = min(minDist, level[x]);
    FOR (i, 0, n) {
        cout << i << ": ";
        for (auto x: g[i]) cout << x << " ";
        cout << endl;
    }
    if (minDist == INT_MAX) cout << "d(V1, V2) = INF" << endl;
    else cout << "d(V1, V2) = " << minDist << endl;

    return 0;
}
