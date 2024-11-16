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
    vi sq;
    FOR (i, 1, 1000) {
        sq.pub(2*i*i);
    }
    ll t; cin >> t;
    while(t--){
        ll n; cin >> n;
        // ll k = 0;
        // for (auto x: sq) {
        //     if (n%x == 0) {
        //         k = x;
        //         break;
        //     }
        // }
        // if (k==0) {
        //     cout << -1 << endl;
        //     continue;
        // }
        // k/=2;
        // ll cntf = 1, cnts = 1;
        // while(n>0) {
        //     FOR (i, 0, k) cout << cntf++ << " ";
        //     FOR (i, 0, k) cout << cnts++ << " ";
        //     n -= 2*k;
        // }
        // cout << endl;
        // int arr[] = {1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 13, 13, 1, 12};
        //         cout << sizeof(arr)/sizeof(arr[0]) << endl;
        if (n&1) {
            if (n >= 27) {
                int arr[] = {1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 13, 13, 1, 12};
                for (auto x: arr) cout << x << " ";
                ll k = n-27;
                k/=2;
                ll cnt = 14;
                FOR (i, 0, k) {
                    cout << cnt << " " << cnt << " ";
                    cnt++;
                }
            }
            else cout << -1 << endl;
        }
        else {
            ll k = n/2;
            FOR (i, 0, k) cout << i+1 << " " << i+1 << " ";
            cout << endl;
        }
    }
    return 0;
}
