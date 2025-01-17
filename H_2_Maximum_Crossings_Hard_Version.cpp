#pragma GCC optimize ("O3", "unroll-loops", "strict-overflow")
#pragma GCC optimize ("trapv")
#pragma GCC target ("avx2", "abm", "bmi", "bmi2", "popcnt", "lzcnt")
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

ll solve (vector<pair<float, float>> &vx, vector<pair<float, float>> &vy, ll l, ll r) {
    if (r-l < 1) return 0;
    ll mid = (l + r) / 2;
    ll linter = solve(vx, vy, l, mid);
    ll rinter = solve(vx, vy, mid + 1, r);

    vector<pair<float, float>> left, right;
    FOR (i, l, mid+1) left.pub(vy[i]);
    FOR (i, mid+1, r+1) right.pub(vy[i]);

    ll i = 0, j = 0, ret = 0;
    while (i < sz(left) || j < sz(right)) {
        if (i < sz(left) && j < sz(right)) {
            if (left[i].ss < right[j].ss) {
                vy[l+i+j] = left[i];
                i++;
            }
            else {
                vy[l+i+j] = right[j];
                j++;
                ret += sz(left) - i;
            }
        }
        else if (i < sz(left)) {
            vy[l+i+j] = left[i];
            i++;
        }
        else {
            vy[l+i+j] = right[j];
            j++;
            ret += sz(left) - i;
        }
    }

    return linter + rinter + ret;
}

int main(){
    fastio();
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        vector<pair<float, float>> vx, vy;
        F0R (i, n) {
            float temp; cin >> temp;
            vx.pub(mp(i+1, temp));
        }
        float f = 1.0 / n;
        F0R (i, n) {
            vx[i].ss += (n-1-i);
            vy.pub(vx[i]);
        }
        
        ll total = solve(vx, vy, 0, n-1);
        cout << total << endl;
    }
    return 0;
}