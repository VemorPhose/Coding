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
    ll t; cin >> t;
    while(t--){
        
    }
    return 0;
}

int binarySearch(vector<int> A, int lo, int hi, int key){
    if(hi == lo){
        if(A[lo] == key)
            return lo;
        return -1;
    }
    int mid = (lo+hi)/2;
    if(A[mid] >= key)
        return binarySearch(A, lo, mid, key);
    else
        return binarySearch(A, mid+1, hi, key);
}

const int N = 1e7 + 10;
vector<bool> primes(N, 1);

void sieve() {
    primes[0] = primes[1] = 0;
    for (int i = 2; i < N; i++) {
        if (primes[i]) {
            for (int j = i + i; j < N; j += i) {
                primes[j] = 0;
            }
        }
    }
}

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

// cut-paste in main
    int v, e; cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int v1, v2; cin >> v1 >> v2;
        g[v1].push_back(v2);
        g[v2].push_back(v1);
    }

const int N = 1e7 + 10;
vector<pair<int, int> > g[N];

int main(){
    fastio();
    int n, m; cin >> n >> m;
    int vertex; cin >> vertex;
    vector<pair<pair<int, int>, int > > edges;
    FOR (i, 0, m) {
        int u, v, w; cin >> u >> v >> w;
        edges.pub(mp(mp(u, v), w));
        g[u].pub(mp(v, w));
    }

    // Bellman Ford Algorithm
    vector<int> shortestPath(n, INT_MAX);
    shortestPath[vertex] = 0;
    FOR (i, 0, n - 1) {
        for (auto x: edges) {
            int u = x.ff.ff;
            int v = x.ff.ss;
            int w = x.ss;
            if (shortestPath[u] != INT_MAX && shortestPath[u] + w < shortestPath[v]) {
                shortestPath[v] = shortestPath[u] + w;
            }
        }
    }

    // Insert negative cycle detection code here
    for (auto x: shortestPath) cout << x << " ";
    cout << endl;

    return 0;
}

const int N = 1e7 + 10;
vector<pair<int, int> > g[N], ans[N]; // MST
bool vis[N];
int key[N];
int parent[N];

struct Comparator {
    bool operator() (pair<int, int> a, pair<int, int> b) {
        return a.ss > b.ss;
    }
};

int main(){
    fastio();
    int n, m; cin >> n >> m;
    int vertex; cin >> vertex;
    FOR (i, 0, m) {
        int u, v, w; cin >> u >> v >> w;
        g[u].pub(mp(v, w));
        g[v].pub(mp(u, w));
    }
    
    // Djikstra Algorithm
    priority_queue<pair<int, int>, vector<pair<int, int> >, Comparator> q;
    vis[vertex] = true;
    int shortestPath[n];
    shortestPath[vertex] = 0;
    FOR (i, 0, n) {
        if (i == vertex) continue;
        key[i] = INT_MAX;
    }
    for (auto x: g[vertex]) {
        if (key[vertex] + x.ss <= key[x.ff]) {
            key[x.ff] = key[vertex] + x.ss;
            parent[x.ff] = vertex;
            q.push(mp(x.ff, key[x.ff]));
        }
    }

    int numVis = 1;
    while (!q.empty() && numVis < n) {
        auto x = q.top(); q.pop();
        if (vis[x.ff]) continue;
        vis[x.ff] = true; numVis++;
        ans[parent[x.ff]].pub(mp(x.ff, x.ss - key[parent[x.ff]]));
        shortestPath[x.ff] = x.ss;
        for (auto y: g[x.ff]) {
            if (!vis[y.ff] && key[y.ff] > key[x.ff] + y.ss) {
                key[y.ff] = key[x.ff] + y.ss;
                parent[y.ff] = x.ff;
                q.push(mp(y.ff, key[y.ff]));
            }
        }
    }

    for (auto x: shortestPath) cout << x << " ";
    cout << endl;

    return 0;
}

const int N = 1e7 + 10;
vector<pair<int, int> > g[N], ans[N]; // MST
bool vis[N];

struct Comparator {
    bool operator() (pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
        return a.ss > b.ss;
    }
};

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
    for (auto x: g[0]) q.push(mp(mp(0, x.ff), x.ss));
    while (szMSTedges < n-1) {
        auto x = q.top(); q.pop();
        if (vis[x.ff.ss]) continue;
        vis[x.ff.ss] = true;
        ans[x.ff.ff].pub(mp(x.ff.ss, x.ss));
        ans[x.ff.ss].pub(mp(x.ff.ff, x.ss));
        MSTedges.pub(mp(mp(x.ff.ff, x.ff.ss), x.ss));
        szMSTedges++;
        for (auto y: g[x.ff.ss]) if (!vis[y.ff]) q.push(mp(mp(x.ff.ss, y.ff), y.ss));
    }

    for (auto p: MSTedges) {
        cout << p.ff.ff << " " << p.ff.ss << " " << p.ss << endl;
    }

    return 0;
}

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

int rankNode[N], parent[N];

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

const int N = 1e7 + 10;
vector<int> g[N], gRev[N];
bool vis[N], visRev[N];
int curTime = 0, vertices = 0;
pair<int, int> timer[N];

void reverseGraph(int v) {
    FOR (i, 0, v) {
        for (auto x: g[i]) {
            gRev[x].pub(i);
        }
    }
}

void dfs(int vertex) {
    vis[vertex] = 1;
    for (int child: g[vertex]) {
        if (vis[child]) continue;
        dfs(child);
    }
    return;
}

void dfsRev(int vertex) {
    visRev[vertex] = 1;
    cout << vertex << " ";
    for (int child: gRev[vertex]) {
        if (visRev[child]) continue;
        dfsRev(child);
    }
    timer[vertices--] = mp(vertex, curTime++);
    return;
}

int main(){
    fastio();
    int v, e; cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int v1, v2; cin >> v1 >> v2;
        g[v1].push_back(v2);
    }
    reverseGraph(v);
    vertices = v-1;
    
    int ptr = 0;
    while (ptr < v) {
        if (!vis[timer[ptr].ff]) {
            dfs(timer[ptr].ff);
            cout << endl;
        }
        ptr++;
    }

    return 0;
}

const int N = 1e7 + 10;
vector<int> g[N], gRev[N];
bool vis[N], visRev[N];

void reverseGraph(int v) {
    FOR (i, 0, v) {
        for (auto x: g[i]) {
            gRev[x].pub(i);
        }
    }
}

void dfs(int vertex) {
    vis[vertex] = 1;
    for (int child: g[vertex]) {
        if (vis[child]) continue;
        dfs(child);
    }
    return;
}

void dfsRev(int vertex) {
    visRev[vertex] = 1;
    for (int child: gRev[vertex]) {
        if (visRev[child]) continue;
        dfsRev(child);
    }
    return;
}

int main(){
    fastio();
    int v, e; cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int v1, v2; cin >> v1 >> v2;
        g[v1].push_back(v2);
    }
    reverseGraph(v);

    dfs(0); dfsRev(0);
    bool flag = true;
    FOR (i, 0, v) flag &= vis[i];
    FOR (i, 0, v) flag &= visRev[i];

    cout << (flag ? "YES" : "NO") << endl;

    return 0;
}


const int N = 1e7 + 10;
vector<int> g[N];
bool vis[N];
bool recStack[N];

int detectCycleHelper (int vertex, int parent) {
    vis[vertex] = 1;
    int ret = 0;
    recStack[vertex] = 1;
    for (int child: g[vertex]) {
        if (recStack[child] && child != parent) return 1;
        if (vis[child]) continue;
        ret |= detectCycleHelper(child, vertex);
    }
    recStack[vertex] = 0;
    return ret;
}

int detectCycle (int v) {
    memset(vis, 0, sizeof(vis));
    memset(recStack, 0, sizeof(recStack));
    int ret = 0;
    for (int i = 0; i < v; i++) {
        ret |= detectCycleHelper(i, -1);
        if (ret) break;
    }
    return ret;
}

int main(){
    fastio();
    int v, e; cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int v1, v2; cin >> v1 >> v2;
        g[v1].push_back(v2);
    }
    cout << detectCycle(v) << endl;
    return 0;
}


ll cache[102][100002];

int main(){
    fastio();
    int n, w; cin >> n >> w;
    int weights[n]; ll values[n];
    FOR (i, 0, n) cin >> weights[i] >> values[i];
    memset(cache, 0, 102 * 100002 * sizeof(int));

    FOR (i, 0, n) {
        FOR (j, 0, w+1) {
            if (cache[i][j] > cache[i+1][j]) 
                cache[i+1][j] = cache[i][j];
            if ((j + weights[i] <= w) && (cache[i+1][j + weights[i]] < cache[i][j] + values[i]))
                cache[i+1][j + weights[i]] = cache[i][j] + values[i];
        }
    }

    // FOR (i, 0, n+1) {
    //     FOR (j, 0, w+1) {
    //         cout << cache[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    ll maxValue = *max_element(cache[n], cache[n] + w+1);
    cout << maxValue << endl;

    return 0;
}
int main(){
    fastio();
    string s, t; cin >> s >> t;
    int n = s.size(), m = t.size();
    int dp[n+1][m+1];
    FOR (i, 0, n+1) dp[i][0] = 0;
    FOR (i, 0, m+1) dp[0][i] = 0;

    FOR (i, 1, n+1) {
        FOR (j, 1, m+1) {
            if (s[i-1] == t[j-1]) dp[i][j] = max(max(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1] + 1);
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    // FOR (j, 0, m+1) {
    //     FOR (i, 0, n+1) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << dp[n][m] << endl;

    string ans = "";
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (s[i-1] == t[j-1]) {
            ans = s[i-1] + ans;
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) i--;
        else j--;
    }
    // reverse(all(ans));
    cout << ans << endl;

    return 0;
}

