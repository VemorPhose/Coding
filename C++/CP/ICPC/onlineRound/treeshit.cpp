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
        int n, d, l;
        cin >> n >> d >> l;

        // if (d % 2 == 0) {
        //     if (n > ((d/2)*l + 1)) {
        //         cout << -1 << endl;
        //         continue;
        //     }
        // } else {
        //     if (n > ((d/2)*l + 2)) {
        //         cout << -1 << endl;
        //         continue;
        //     }
        // }

        if (n < d + l - 1) {
            cout << -1 << endl;
            continue;
        }

        vector<pair<int, int>> edges;
        queue<pair<int, int>> q;

        FOR (i, 1, d+1) {
            edges.pub(mp(i, i+1));
        }
        int node = d+2;
        int base = node/2;
        FOR (i, 0, l-2) {
            edges.pub(mp(base, node));
            q.push(mp(node, 1));
            node++;
        }
        bool flag = true;
        while (node <= n) {
            if (q.empty()) {
                flag = false;
                break;
            }
            auto p = q.front(); q.pop();
            if (p.ss >= d/2) continue;
            edges.pub(mp(p.ff, node));
            q.push(mp(node, p.ss+1));
            node++;
        }
        if (!flag) {
            cout << -1 << endl;
            continue;
        }
        for (auto x: edges) {
            cout <<x.ff<<" "<<x.ss<<endl;
        }
    }
    return 0;
}
