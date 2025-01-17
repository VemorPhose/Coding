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

pair<float, pair<pii, pii>> solve (vector<pii>& vx, vector<pii>& vy, ll l, ll r) {
    if (r-l < 1) return mp(-1, mp(mp(0, 0), mp(0, 0)));
    if (r-l == 1) {
        ll a = vx[l].ff - vx[r].ff;
        ll b = vx[l].ss - vx[r].ss;
        if (vy[l].ss > vy[r].ss) {
            auto temp = vy[l];
            vy[l] = vy[r];
            vy[r] = temp;
        }
        return mp(sqrt(a*a + b*b), mp(vx[l], vx[r]));
    }

    ll mid = (l+r)/2;
    auto ldis = solve(vx, vy, l, mid);
    auto rdis = solve(vx, vy, mid+1, r); 
    auto dis = ldis.ff < rdis.ff ? ldis : rdis;
    if (ldis.ff == -1) dis = rdis;
    if (rdis.ff == -1) dis = ldis;
    float meanx = (vx[mid].ff + vx[mid+1].ff)/2.0;
    float leftx = meanx - dis.ff, rightx = meanx + dis.ff;

    vector<pii> left, right;
    FOR (i, l, mid+1) {
        left.pub(vy[i]);
    }
    FOR (i, mid+1, r+1) {
        right.pub(vy[i]);
    }
    // for (auto x: left) {
    //     cout << x.ff << " " << x.ss << endl;
    // }
    // cout << sz(left) << endl;
    // for (auto x: right) {
    //     cout << x.ff << " " << x.ss << endl;
    // }
    // cout << sz(right) << endl;
    ll i = 0, j = 0;
    while (i < sz(left) || j < sz(right)) {
        // cout << "a " << i << " " << j << endl;
        if (i < sz(left) && j < sz(right)) {
            if (left[i].ss < right[j].ss) {
                vy[l+i+j] = left[i];
                i++;
            }
            else {
                vy[l+i+j] = right[j];
                j++;
            }
        }
        else if (i < sz(left)) {
            vy[l+i+j] = left[i];
            i++;
        }
        else {
            vy[l+i+j] = right[j];
            j++;
        }
    }

    vector<pii> slice;
    FOR (i, l, r+1) {
        if (vy[i].ff >= leftx && vy[i].ff <= rightx) {
            slice.pub(vy[i]);
        }
    }
    FOR (i, 0, sz(slice)) {
        FOR (j, 0, 8) {
            if (j == 0 || i + j < 0 || i + j >= sz(slice)) continue;
            ll a = slice[i].ff - slice[i+j].ff;
            ll b = slice[i].ss - slice[i+j].ss;
            float temp = sqrt(a*a + b*b);
            if (temp < dis.ff)
                dis = mp(temp, mp(slice[i], slice[i+j]));
        }
    }

    // FOR (i, l, r+1) {
    //     cout << vy[i].ff << " " << vy[i].ss << endl;
    // }
    // cout << fixed << setprecision(2) << ldis.ff << endl;
    // cout << ldis.ss.ff.ff << " " << ldis.ss.ff.ss << " , " << ldis.ss.ss.ff << " " << ldis.ss.ss.ss << endl;
    // cout << fixed << setprecision(2) << rdis.ff << endl;
    // cout << rdis.ss.ff.ff << " " << rdis.ss.ff.ss << " , " << rdis.ss.ss.ff << " " << rdis.ss.ss.ss << endl;
    // cout << endl;
    return dis;
}

int main(){
    // fastio();
    int n; cin >> n;
    vector<pii> vx, vy;
    FOR (i, 0, n) {
        int x, y; cin >> x >> y;
        vx.pub(mp(x, y));
    }

    sort(all(vx));
    FOR (i, 0, n) {
        vy.pub(vx[i]);
    }
    
    auto dis = solve(vx, vy, 0, n-1);
    cout << fixed << setprecision(2) << dis.ff << endl;
    cout << dis.ss.ff.ff << " " << dis.ss.ff.ss << " , " << dis.ss.ss.ff << " " << dis.ss.ss.ss << endl;

    return 0;
}