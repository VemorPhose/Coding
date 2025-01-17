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
        ll n, k; cin >> n >> k;
        vi v; vIn(v, n);
        if (k == 0) {
            ll total = accumulate(all(v), 0);
            total /= n;
            ll ans = 0;
            FOR(i, 0, n) ans = max(ans, abs(v[i] - total));
            cout << ans << endl;
            continue;
        }
        if (k >= n-1) {
            cout << 0 << endl;
            continue;
        }
        vector<pii> vp;
        FOR(i, 0, n-1) {
            vp.pub(mp(abs(v[i+1] - v[i]), i));
        }
        sort(all(vp), greater<pii>());
        // for (auto x: vp) cout << x.ss << " ";
        // cout << endl;
        vector<pii> intervals;
        FOR(i, 0, k) {
            int ind = vp[i].ss;
            int dist = vp[i].ff;
            intervals.pub(mp(ind, dist));
        }
        sort(all(intervals));
        ll m = sz(intervals);
        // for (auto x: intervals) cout << x.ff << " ";
        // cout << endl;

        vi b(n);
        ll total = 0;
        ll maxm = INT_MIN, minm = INT_MAX;
        FOR(i, 0, intervals[0].ff + 1) {
            maxm = max(maxm, v[i]);
            minm = min(minm, v[i]);
        }
        total = (minm + maxm)/2;
        FOR(i, 0, intervals[0].ff + 1) {
            b[i] = total;
        }
        FOR(i, 0, m-1) {
            int l = intervals[i].ff + 1;
            int r = intervals[i+1].ff + 1;
            // cout << l << " " << r << endl;
            maxm = INT_MIN;
            minm = INT_MAX;
            FOR(j, l, r) {
                maxm = max(maxm, v[j]);
                minm = min(minm, v[j]);
            }
            total = (minm + maxm)/2;
            // cout << total << endl;
            FOR(j, l, r) {
                b[j] = total;
            }
        }
        maxm = INT_MIN;
        minm = INT_MAX;
        FOR(i, intervals[m-1].ff + 1, n) {
            maxm = max(maxm, v[i]);
            minm = min(minm, v[i]);
        }
        total = (minm + maxm)/2;
        FOR(i, intervals[m-1].ff + 1, n) {
            b[i] = total;
        }
        ll ans = 0;
        FOR(i, 0, n) ans = max(ans, abs(b[i] - v[i]));
        // for (auto x: b) cout << x << " ";
        // cout << endl;
        cout << ans << endl;
    }
    return 0;
}
