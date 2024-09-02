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

bool cmp(pii a, pii b) {
    return a.ss < b.ss;
}

float solve (vector<pii>& vx, vector<pii>& vy, ll l, ll r) {
    if (r-l < 1) return -1;
    if (r-l == 1) {
        ll a = vx[l].ff - vx[r].ff;
        ll b = vx[l].ss - vx[r].ss;
        if (vy[l].ss > vy[r].ss) {
            auto temp = vy[l];
            vy[l] = vy[r];
            vy[r] = temp;
        }
        return sqrt(a*a + b*b);
    }
    ll mid = (l+r)/2;
    float ldis = solve(vx, vy, l, mid);
    float rdis = solve(vx, vy, mid+1, r); 
}

int main(){
    fastio();
    int n; cin >> n;
    vector<pii> vx, vy;
    FOR (i, 0, n) {
        int x, y; cin >> x >> y;
        vx.pub(mp(x, y));
        vy.pub(mp(x, y));
    }

    sort(all(vx));
    sort(all(vy));

    return 0;
}