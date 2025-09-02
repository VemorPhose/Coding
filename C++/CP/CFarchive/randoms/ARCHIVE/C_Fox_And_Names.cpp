#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

const int N = 27;
vector<int> g[N];
bool vis[N];
bool ancestor[N];

bool cycle(int vertex, int parent) {
    // Take action on vertex after entering the vertex
    vis[vertex] = 1;
    ancestor[vertex] = 1;
    bool cycleInChildren = false;
    for (int child: g[vertex]) {
        if (ancestor[child] && child != parent) return true;
        if (vis[child]) continue;
        // Take action on child before entering the child node
        cycleInChildren |= cycle(child, vertex);
        // Take action on child after exiting the child node
    }
    // Take action on vertex before exiting the vertex
    ancestor[vertex] = false;
    return cycleInChildren;
}

int getID(char c) {
    if (c == ' ') return 0;
    return c - 'a' + 1;
}

int main(){
    fastio();
    ll n; cin >> n;
    vector<string> v;
    FOR (i, 0, n) {
        string temp; cin >> temp; temp.pub(' ');
        v.pub(temp);
    }

    bool imflag = false;
    FOR (i, 1, n) {
        string s1 = v[i-1];
        string s2 = v[i];
        ll ind = 0;
        while (ind < sz(s1) && ind < sz(s2) && s1[ind] == s2[ind]) ++ind;
        if (ind == sz(s1) || ind == sz(s2)) continue;
        ll id1 = getID(s1[ind]);
        ll id2 = getID(s2[ind]);
        if (id2 == 0) {
            imflag = true;
            break;
        }
        else if (id1 == 0) continue;
        g[id1].pub(id2);
    }

    // FOR (i, 0, N) {
    //     for (auto x: g[i]) {
    //         cout << x << " ";
    //     }
    //     cout << endl;
    // }

    bool containsCycle = cycle()

    return 0;
}