// 雪雁不浴自白，人亦无为而自成。
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
    while(true) {
        string s; cin >> s;
        if(s == "end") break;
        int x = 0, o = 0;
        for(char &c: s) {
            if(c == 'X') x++;
            else if(c == 'O') o++;
        }
        if(x-o != 0 && x-o != 1) {
            cout << "invalid" << endl;
            continue;
        }
        char winner = 'X';
        if(x == o) winner = 'O';
        vector<vector<int>> pats;
        pats.pub({0,1,2});
        pats.pub({3,4,5});
        pats.pub({6,7,8});
        pats.pub({0,3,6});
        pats.pub({1,4,7});
        pats.pub({2,5,8});
        pats.pub({0,4,8});
        pats.pub({2,4,6});
        bool flag = 0;
        for(auto pat: pats) {
            if(s[pat[0]] == winner && s[pat[1]] == winner && s[pat[2]] == winner) {
                flag = 1;
                break;
            }
        }
        if(flag) cout << "valid" << endl;
        else if(x+o == 9) cout << "valid" << endl;
        else cout << "invalid" << endl;
    }
    return 0;
}
