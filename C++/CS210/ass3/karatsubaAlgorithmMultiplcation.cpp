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

ll binexp(ll base, ll pow) {
    if (pow == 0) return 1;
    else if (pow&1) return base * binexp(base, pow/2) * binexp(base, pow/2);
    else return binexp(base, pow/2) * binexp(base, pow/2);
}

ll digits(ll n) {
    ll cnt = 0;
    while (n) {
        n /= 10;
        cnt++;
    }
    return cnt;
}

ll karatsuba (ll a, ll b) {
    if (a/10 == 0 || b/10 == 0) 
        return a * b;
    ll na = digits(a), nb = digits(b);
    ll fa = binexp(10, na/2), fb = binexp(10, nb/2);
    ll a1 = a/fa, a2 = a%fa, b1 = b/fb, b2 = b%fb;
    ll A = karatsuba(a1, b1);
    ll B = karatsuba(a2, b2);
    ll C = (a1+a2)*(b1+b2) - A - B;
    return (A * fa * fb) + (C * ((fa + fb) / 2)) + B;
}

int main(){
    fastio();
    ll a, b; cin >> a >> b;
    ll out = karatsuba(a, b);
    cout << out << endl;
    return 0;
}