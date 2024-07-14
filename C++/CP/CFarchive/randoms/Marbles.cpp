// made by Vemor Phose
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

// typedefs
#define ll              int_fast64_t
#define ull             uint_fast64_t
#define int             int_fast32_t
#define uint            uint_fast32_t
#define pii             pair<ll, ll>
#define vi              vector<ll>
#define vvi             vector<vector<ll>>
#define mpii            map<ll, ll>
#define umpii           unordered_map<ll, ll>
#define vs              vector<string>

// shortcuts
#define MOD             1e9+7
#define mod             998244353
#define INF             1e18+10
#define PI              2 * acos(0.0)
#define LL_MAX          LLONG_MAX
#define LL_MIN          LLONG_MIN
#define ULL_MAX         ULLONG_MAX
#define endl            "\n"

// general
#define fastio()        ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define arrIn(arr, n)   for(ll i = 0; i < n; i++) cin >> arr[i]
#define vIn(v, n)       for(ll i = 0; i < n; i++) { ll temp; cin >> temp; v.pub(temp); }
#define coutN           cout << "NO" << endl
#define coutY           cout << "YES" << endl

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
#define FOR(i, a, b)    for (int i = (a); i < (b); ++i)
#define F0R(i, a)       FOR(i, 0, a)
#define ROF(i, a, b)    for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a)       ROF(i, 0, a)

int main(){
    fastio();
    int t; cin >> t;
    while(t--){
        ll a, b; cin>>a>>b;
        ll minct = LL_MAX;
        ll cnt = 0;
        if(a%b==0){
            cout << 0 << endl;
            continue;
        }
        ll a1 = a, b1 = b;
        while(b1 > 1){
            ++cnt;
            --b1;
            ++a1;
            if(a1%b1==0){
                if(cnt < minct) minct = cnt;
                break;
            }
        }
        a1 = a; b1 = b; cnt = 0;
        while(a1-b1 >= 2){
            ++cnt;
            ++b1;
            --a1;
            if(a1%b1==0){
                if(cnt < minct) minct = cnt;
                break;
            }
        }
        cout << minct << endl;
    }
    return 0;
}