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

pii solve (vi *v, ll target, pii l, pii r) {
    if (l.ff > r.ff || l.ss > r.ss) return mp(-1, -1);
    else if (l.ff == r.ff && l.ss == r.ss) {
        if (v[l.ff][l.ss] == target) return mp(l.ff, l.ss);
        else return mp(-1, -1);
    }

    pii trav = l;
    while (trav.ff < r.ff && trav.ss < r.ss) {
        if (v[trav.ff][trav.ss] < target) {
            trav.ff++;
            trav.ss++;
        }
        else break;
    }

    if (v[trav.ff][trav.ss] == target) return trav;
    else if (v[trav.ff][trav.ss] > target) {
        pii up = solve(v, target, mp(l.ff, trav.ss), mp(trav.ff - 1, r.ss));
        pii down = solve(v, target, mp(trav.ff, l.ss), mp(r.ss, trav.ss - 1));
        if (up.ff == -1 && up.ss == -1) return down;
        else return up;
    }
    else {
        pii up = solve(v, target, mp(l.ff, trav.ss + 1), mp(trav.ff, r.ss));
        pii down = solve(v, target, mp(trav.ff + 1, l.ss), mp(r.ss, trav.ss));
        if (up.ff == -1 && up.ss == -1) return down;
        else return up;
    }
}

int main(){
    fastio();
    ll n, q; cin >> n >> q;
    vi v[n];
    FOR (i, 0, n) vIn(v[i], n);
    while (q--) {
        ll target; cin >> target;
        pii ans = solve(v, target, mp(0, 0), mp(n - 1, n - 1));
        if (ans.ff == -1 && ans.ss == -1) cout << -1 << endl;
        else cout << ans.ff + 1 << " " << ans.ss + 1 << endl;
    }
    return 0;
}