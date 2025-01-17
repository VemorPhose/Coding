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
        ll n, m, l; cin >> n >> m >> l;
        vector<pii> hur, buff;
        F0R(i, n) {
            ll x, y; cin >> x >> y;
            hur.pub(mp(x, y));
        }
        sort(all(hur));
        F0R(i, m) {
            ll x, y; cin >> x >> y;
            buff.pub(mp(x, y));
        }
        sort(all(buff));

        ll pos = 1, k = 1;
        ll indBuff = 0;
        ll numBuffs = 0;
        bool possible = true;
        priority_queue<ll> q;
        for (auto x: hur) {
            // if (x.ff > l) break;
            // else if (x.ff <= l && x.ss >= l) {
            //     possible = false;
            //     break;
            // }
            pos = x.ff-1;
            while (indBuff < m && buff[indBuff].ff < x.ff) {
                q.push(buff[indBuff].ss);
                indBuff++;
            }
            while (!q.empty() && k <= (x.ss-x.ff+1)) {
                k += q.top();
                q.pop();
                numBuffs++;
            }
            if (q.empty() && k<= (x.ss-x.ff+1)) {
                possible = false;
                break;
            }
        }
        if (possible) cout << numBuffs << endl;
        else cout << -1 << endl;
    }
    return 0;
}
