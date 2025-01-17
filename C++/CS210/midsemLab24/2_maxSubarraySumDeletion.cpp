#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
using namespace std;
// template <typename T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

pair<ll, ll> solve (vi nums, ll l, ll r) {
    if (r < l) return mp(LL_MIN, 0);
    if (r == l) return mp(nums[l], 0);

    ll mid = (l + r)/2;
    pair<ll, ll> left = solve (nums, l, mid);
    pair<ll, ll> right = solve (nums, mid+1, r);
    if (left.ff == LL_MIN) left = right;
    else if (right.ff == LL_MIN) right = left;

    ll preleft[sz(nums)], preright[sz(nums)], minleft[sz(nums)], minright[sz(nums)];
    ll maxleft = mid, maxright = mid+1;
    for (int i = mid; i >= l; i--) {
        if (i == mid) {
            preleft[i] = nums[i];
            minleft[i] = nums[i];
        }
        else {
            preleft[i] = preleft[i+1] + nums[i];
            minleft[i] = min(minleft[i+1], nums[i]);
            maxleft = preleft[i] >= preleft[maxleft] ? i : maxleft;
        }
    }
    ll maxleftval = preleft[maxleft], maxleftrem = maxleftval - minleft[maxleft];
    for (int i = mid+1; i <= r; i++) {
        if (i == mid+1) {
            preright[i] = nums[i];
            minright[i] = nums[i];
        }
        else {
            preright[i] = preright[i-1] + nums[i];
            minright[i] = min(minright[i-1], nums[i]);
            maxright = preright[i] >= preright[maxright] ? i : maxright;
        }
    }
    ll maxrightval = preright[maxright], maxrightrem = maxrightval - minright[maxright];
    
    ll temp = max(maxleftval + maxrightrem, maxrightval + maxleftrem);
    auto ptemp = left.ff > right.ff ? left : right;
    pair<ll, ll> p;
    if (temp > maxrightval + maxleftval) {
        p = mp(temp, 1);
    }
    else {
        p = mp(maxleftval+maxrightval, 0);
    }
    // cout << left.ff << " " << right.ff << " " << p.ff << " " << ptemp.ff << endl;
    return ptemp.ff > p.ff ? ptemp : p;
}

int main(){
    fastio();
    ll n; cin >> n;
    vi nums; vIn(nums, n);

    auto ans = solve(nums, 0, n-1);
    cout << ans.ff << endl;
    return 0;
}