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

bool vis[1000][1000];

int main(){
    fastio();
    ll t; cin >> t;
    while(t--){
        int n, m; cin >> n >> m;
        string arr[n];
        FOR (i, 0, n) cin >> arr[i];
        memset(vis, false, sizeof(vis));
        int t = 0, b = n-1, l = 0, r = m-1;
        int ans = 0;
        // find pattern "1543" while going in circle in the matrix
        while(l <= r && t <= b){
            int i = 0, j = 0;
            int cnt = 0;
            FOR (cc, 0, 4 * (b+r-t-l+2)) {
                if (arr[i][j]=='1') cnt = 1;
                else if (arr[i][j] == '5' && cnt == 1) cnt = 2;
                else if (arr[i][j] == '4' && cnt == 2) cnt = 3;
                else if (arr[i][j] == '3' && cnt == 3) cnt = 4;
                if (cnt == 4) {
                    if (!vis[i][j]) {
                        ans++;
                        vis[i][j] = true;
                    }
                    else cnt = 0;
                }
                if (i == t && j != r) j++;
                else if (j == r && i != b) i++;
                else if (i == b && j != l) j--;
                else i--;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
