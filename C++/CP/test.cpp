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
#define FOR(i, a, b)    for (int i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)
#define ROF(i, a, b)    for (int i = (b)-1; i >= (a); --i)
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

void dfs(int vertex) {
    // Take action on vertex after entering the vertex
    vis[vertex] = 1;
    for (int child: g[vertex]) {
        if (vis[child]) continue;
        // Take action on child before entering the child node
        dfs(child);
        // Take action on child after exiting the child node
    }
    // Take action on vertex before exiting the vertex
    return;
}

int level[N];

void bfs(int vertex) {
    queue<int> q;
    q.push(vertex);
    vis[vertex] = 1;
    level[vertex] = 0;

    while (!q.empty()) {
        int cur_v = q.front();
        q.pop();
        for (int child: g[cur_v]) {
            if (!vis[child]) {
                q.push(child);
                vis[child] = 1;
                level[child] = level[cur_v] + 1;
            }
        }
    }
}

int main(){
    fastio();
    // cut-paste in main
    int v, e; cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int v1, v2; cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }
    return 0;
}