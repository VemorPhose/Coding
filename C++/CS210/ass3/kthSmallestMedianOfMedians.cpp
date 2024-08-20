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

ll pivot (vi v) {
    // for (auto x: v) cout << x << " "; cout << endl;
    vi vMedians = v, vBuf;
    while (sz(vMedians) > 5) {
        for (ll i = 0; i < sz(vMedians); i += 5) {
            sort (vMedians.begin() + i, vMedians.begin() + min(i+5, sz(vMedians)));
            if (i+5 <= sz(vMedians)) vBuf.pub(vMedians[i+2]);
            else vBuf.pub(vMedians[i + (sz(vMedians)-1-i)/2]);
        }
        vMedians = vBuf;
        vBuf.clear();
        // for (auto x: vMedians) cout << x << " "; cout << endl;
    }
    return find(all(v), vMedians[sz(vMedians)/2]) - v.begin();
}

ll partition (vi& v) {
    // for (auto x: v) cout << x << " "; cout << endl;
    ll indpiv = pivot (v), x = v[indpiv];
    // cout << x << endl;
    vi vl, vr;
    ll cnt = 0;
    FOR (i, 0, sz(v)) {
        if (v[i] == v[indpiv]) cnt++;
        else if (v[i] < v[indpiv])
            vl.pub(v[i]);
        else vr.pub(v[i]);
    }
    while(cnt--) vl.pub(v[indpiv]);
    for(auto x: vr) vl.pub(x);
    v = vl;
    // for (auto x: v) cout << x << " "; cout << endl;
    return find(all(v), x) - v.begin();
}

ll kthSmallest (vi& v, ll k) {
    // for (auto x: v) cout << x << " "; cout << endl;
    if (sz(v) == 1) {
        return v[0];
    }
    else if (sz(v) == 2) {
        if (k==1) return (v[0] > v[1] ? v[1] : v[0]);
        else return (v[0] > v[1] ? v[0] : v[1]);
    }
    ll indpiv = partition(v);
    vi vnew;
    if (indpiv+1 > k) {
        FOR (i, 0, indpiv) {
            vnew.pub(v[i]);
        }
        return kthSmallest(vnew, k);
    }
    else {
        FOR (i, indpiv, sz(v)) {
            vnew.pub(v[i]);
        }
        return kthSmallest(vnew, k - indpiv);
    }
}

int main(){
    fastio();
    ll n, k; cin >> n >> k;
    vi v; vIn(v, n);
    cout << kthSmallest(v, k) << endl;
    return 0;
}